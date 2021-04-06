#include "delegate.h"
#include "listener.h"
#include "viewmodel.h"
#include "messaging_exceptions.h"
#include <iostream>
#include <thread>
#include "messages.h"
#include <QStandardPaths>
#include <QDir>
#include "logger.h"
#include "csvlist.h"
#include <ctime>
#include "ftp.h"
#include "socket.h"
#include "../common/threadpool.h"
#include <sys/time.h>
#include <QDomDocument>
#include <QDomNodeList>
#include <QtNetwork>
#include <QUrl>
#include <QString>

static const char defaultUrl[] = "http://localhost:10080/icamera/cams/ip/";
static const char defaultFileName[] = "response.xml";

QString viewmodel::getUniqueFileName()
{
    time_t t = time(nullptr);
    tm *ltm = localtime(&t);
    char buffer[32];
    size_t sz = strftime(buffer, 32, "%Y%m%d%H%M%S", ltm);
    buffer[sz] = '\0';
    std::string uqName{buffer};
    uqName.append("_");
    uqName.append(m_clientID.c_str());
    return QString::fromStdString(uqName);
}


using namespace Messaging;
void viewmodel::OnAcknowledgement(const char *from, const char *args)
{
    LOGINFOZ("%s -ack-> %s", from, args);
}

void viewmodel::OnException(const char *from, const char *args)
{
    LOGERRZ("%s -err-> %s", from, args);
    throw Messaging::UnknownMessageException();
}

void viewmodel::OnStartRecording(const char *from, const char *args)
{
    auto name = getUniqueFileName();
    setFileName(name);
    LOGINFOZ("Target media file: %s", fileName().toStdString().c_str());
    LOGINFO("Starting recording..");
    setBody("Received: Start Recording");
    QString baseurl = "http://localhost:10080/icamera/cams/ip/startrec/";
    baseurl.append(name);
    const QUrl newUrl = QUrl::fromUserInput(baseurl);
    m_fileName = "";
    emit onRequestReady(newUrl);
}

void viewmodel::OnStopRecording(const char *from, const char *args)
{
    LOGINFO("Stopping recording..");
    static int num = 0;
    setBody("Received: Stop Recording");
    setIsRecording(false);
    QString baseurl = "http://localhost:10080/icamera/cams/ip/stoprec";
    const QUrl newUrl = QUrl::fromUserInput(baseurl);
    emit onRequestReady(newUrl);

    LOGINFOZ("Sending %s to server..", m_fileName.toStdString().c_str());
    setBody("File found");
    QString serverIP{m_epFTP.c_str()};


    auto list = m_fileName.split("|", QString::SplitBehavior::SkipEmptyParts);
    for(auto fileToFTP: list)
    {
        ThreadPool::Factory()->Create([this, serverIP, fileToFTP](){
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            ftp_t ftp(serverIP.toStdString().c_str(), 21);
            ftp.login("sportspip", "drake8283");

            QFileInfo fInfo(fileToFTP);
            QString bname = fInfo.baseName();
            QString fname = bname.append(".").append(fInfo.completeSuffix());
            struct timeval t1, t2;
            gettimeofday(&t1, nullptr);
            size_t szFile = ftp.put_file(fileToFTP.toStdString().c_str(), fname.toStdString().c_str());
            gettimeofday(&t2, nullptr);
            int transferTime = (t2.tv_sec - t1.tv_sec) * 1000 + (t2.tv_usec - t1.tv_usec)/1000;
            auto kbSzFile = szFile/1024;
            auto mbSzFile = kbSzFile/1024;
            LOGINFOZ("FTP_PUSH|%s|%.2f|%d", fname.toStdString().c_str(), mbSzFile, transferTime);
            this->videoFTPComplete(fname);
        });
    }
}

void viewmodel::OnUnknownMessage(const char *from, const char *args)
{
    LOGWARNZ("%s -ukn-> %s", from, args);
}

void viewmodel::OnReplySources(const char *from, const char *args)
{
    if(sizeof (args) > 0)
    {
        CSVList::row list;
        CSVList::split(args, ",", &list);
        if(list.size() > 0)
        {
            m_epSrcs.insert(m_epSrcs.begin(), list.begin(), list.end());
        }
    }
}

void viewmodel::OnHandshakeId(const char *from, const char *args)
{
    m_clientID = args;
}

void viewmodel::startRequest(const QUrl &requestedUrl)
{
    url = requestedUrl;
    httpRequestAborted = false;
    QHttpMultiPart *http = new QHttpMultiPart;

    reply = qnam.post(QNetworkRequest(url), http);
    connect(reply, &QNetworkReply::finished, this, &viewmodel::httpFinished);
    connect(reply, &QIODevice::readyRead, this, &viewmodel::httpReadyRead);
}
void viewmodel::httpFinished()
{

    if (httpRequestAborted) {
        reply->deleteLater();
        reply = Q_NULLPTR;
        return;
    }

    if (reply->error()) {
        reply->deleteLater();
        reply = Q_NULLPTR;
        return;
    }

    const QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);

    reply->deleteLater();
    reply = Q_NULLPTR;

    if (!redirectionTarget.isNull()) {
        const QUrl redirectedUrl = url.resolved(redirectionTarget.toUrl());
        startRequest(redirectedUrl);
        return;
    }


}

void viewmodel::httpReadyRead()
{
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    auto response = reply->readAll();
    QDomDocument doc;
    doc.setContent(response);
    QDomNodeList list=doc.elementsByTagName("string");
    if(m_fileName == "")
    {
        m_fileName=list.at(0).toElement().text();
    }
    else{
        auto path = list.at(0).toElement().text();
    }
}

void viewmodel::setMaximum(int maximum)
{
    m_maximum = maximum;
}

void viewmodel::setValue(int progress)
{
    m_progress = progress;
}
viewmodel::viewmodel(QObject *parent) :
    QObject(parent),
    m_header{""},
    m_body{""},
    m_footer{""},
    m_isRecording{false},
    m_broker{this},
    m_listener{PORT},
    httpRequestAborted(false),
    m_maximum{0},
    m_progress{0}
{    
    LOGINFO("Initializing local storage..");
    QString localPath = QStandardPaths::writableLocation( QStandardPaths::MoviesLocation );
    LOGINFOZ("Storage root: %s", localPath.toStdString().c_str());

    QString appMediaFolder = localPath.append("/SportsPIP/Videos");
    LOGINFOZ("Media folder: %s", appMediaFolder.toStdString().c_str());

    QDir dAppMediaFolder(appMediaFolder);
    if (!dAppMediaFolder.exists())
    {
        LOGINFO("Creating media folder");
        dAppMediaFolder.mkpath(".");
    }
    m_appMediaFolder = appMediaFolder;
    LOGINFOZ("Media folder %s", m_appMediaFolder.toStdString().c_str());

    m_multListener.Start([&](const std::string & serverId, const std::string &msgType, const std::string & broadcast){
        LOGINFOZ("Broadcast received %s", broadcast.c_str());
        m_epSrv = "tcp://" + broadcast + ":8285";
        m_epFTP = broadcast;
        emit this->ftpServerNotified(QString::fromStdString(m_epFTP));
        if(Messaging::Messages::IsRegistered())
            m_messenger.Send(m_epSrv,
                             Messaging::Messages::Factory()->
                             MSG_HDSK(Messaging::MSG_ROLES_ENUM::SOURCE));
    });
    connect(this, &viewmodel::onRequestReady, this, &viewmodel::startRequest);
}

viewmodel::~viewmodel()
{
    this->m_close = true;
}

void viewmodel::start()
{
    m_listener.Listen([&](const std::string &msg) {
        std::cout << "Received: " << msg << std::endl;
        m_broker.OnReceived(msg);
    });
}

QString viewmodel::header()
{
    return m_header;
}

QString viewmodel::body()
{
    return m_body;
}

QString viewmodel::footer()
{
    return m_footer;
}

void viewmodel::setHeader(const QString &val)
{
    m_header = val;
    emit headerChanged();
}

void viewmodel::setBody(const QString &val)
{
    m_body = val;
    emit bodyChanged();
}

void viewmodel::setFooter(const QString &val)
{
    m_footer = val;
    emit footerChanged();
}

void viewmodel::ipSelected(QString ip)
{
    char localAddress[64] = {0};
    sprintf(localAddress, "tcp://%s:%d", ip.toStdString().c_str(), PORT);
    m_localServer = localAddress;
    Messaging::Messages::Factory()->Register(localAddress);
    LOGINFOZ("Local address set to %s", localAddress);
    if(!m_epSrv.empty())
        m_messenger.Send(m_epSrv,
                         Messaging::Messages::Factory()->
                         MSG_HDSK(Messaging::MSG_ROLES_ENUM::SOURCE));
}

void viewmodel::videoFTPComplete(const QString &vid)
{
    m_messenger.Send(m_epSrv, Messaging::Messages::Factory()->MSG_VFTP(vid.toStdString().c_str()));
}

void viewmodel::networkReplyProgress(qint64 bytesRead, qint64 totalBytes)
{
    setMaximum(totalBytes);
    setValue(bytesRead);
}
