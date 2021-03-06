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



using namespace Messaging;
void viewmodel::OnAcknowledgement(const char *from, const char *args)
{

}

void viewmodel::OnException(const char *from, const char *args)
{
    LOGERRZ("%d>> %s", from, args);
    throw Messaging::UnknownMessageException();
}

void viewmodel::OnNewVideoAvailable(const char *from, const char *args)
{

}

void viewmodel::OnSubscription(const char *from, const char *args)
{

}

void viewmodel::OnStartRecording(const char *from, const char *args)
{
    LOGINFO("Starting recording..");
    setBody("Received: Start Recording");
    setIsRecording(true);
}

void viewmodel::OnStopRecording(const char *from, const char *args)
{
    LOGINFO("Stopping recording..");
    static int num = 0;
    setBody("Received: Stop Recording");
    QString filename = "sample.mp4";
    setIsRecording(false);

    LOGINFOZ("Sending %s to server..", m_fileName.data());
    setBody("File found");
    m_ftp.Send(m_fileName);
}

void viewmodel::OnVideoFTPComplete(const char *from, const char *args)
{

}

void viewmodel::OnUnknownMessage(const char *from, const char *args)
{

}

void viewmodel::OnSourceIdle(const char *from, const char *args)
{

}

viewmodel::viewmodel(QObject *parent) :
    QObject(parent),
    m_header{""},
    m_body{""},
    m_footer{""},
    m_isRecording{false},
    m_broker{this},
    m_listener{PORT},
    m_ftp{"192.168.1.166"}
{    
    LOGINFO("Initializing local storage..");
    QString localPath = QStandardPaths::writableLocation( QStandardPaths::MoviesLocation );
    LOGINFOZ("Storage root: %s", localPath.data());

    QString appMediaFolder = localPath.append("/SportsPIP/Videos");
    LOGINFOZ("Media folder: %s", appMediaFolder.data());

    QDir dAppMediaFolder(appMediaFolder);
    if (!dAppMediaFolder.exists())
    {
        LOGINFO("Creating media folder");
        dAppMediaFolder.mkpath(".");
    }
    m_fileName = appMediaFolder.append("/video1.mp4");
    LOGINFOZ("Target media file: %s", m_fileName.data());
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
    Messaging::Messages::Factory()->Register(localAddress);
    LOGINFOZ("Local address set to %s", localAddress);
}
