#include "viewmodel.h"
#include <iostream>
#include "messaging_exceptions.h"
#include "logger.h"
#include "messages.h"
#include <QStandardPaths>
#include <QDir>

void viewmodel::OnAcknowledgement(const char *from, const char *args)
{
    LOGINFOZ("%s -ack-> %s", from, args);
}

void viewmodel::OnException(const char *from, const char *args)
{
    LOGERRZ("%s -err-> %s", from, args);
    throw Messaging::UnknownMessageException();
}

void viewmodel::OnNewVideoAvailable(const char *from, const char *args)
{
    LOGINFOZ("Fetching video from FTP server %s", args);
    QString serverIP{m_epFTP.c_str()};
    m_ftp.Fetch(args, serverIP, m_appMediaFolder.toStdString());
}

void viewmodel::OnUnknownMessage(const char *from, const char *args)
{
    LOGWARNZ("%s -ukn-> %s", from, args);
}

viewmodel::viewmodel(QObject *parent) :
    QObject(parent),
    m_val(-1),
    m_listener{PORT},
    m_broker{this}
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
    m_appMediaFolder = appMediaFolder;
    m_multListener.Start([&](const std::string & serverId, const std::string &msgType, const std::string & broadcast){
        LOGINFOZ("Broadcast received %s", broadcast.c_str());
        m_epSrv = "tcp://" + broadcast + ":8285";
        m_epFTP = broadcast;
        if(Messaging::Messages::IsRegistered())
            m_messenger.Send(m_epSrv,
                             Messaging::Messages::Factory()->
                             MSG_HDSK(Messaging::MSG_ROLES_ENUM::CONSUMER));
    });

    connect(&m_ftp, &FTPClient::videoFetchComplete, this, &viewmodel::videoFetchComplete);
}

void viewmodel::start()
{
    m_listener.Listen([&](const std::string &msg) {
        std::cout << "Received: " << msg << std::endl;
        m_broker.OnReceived(msg);
    });
}

void viewmodel::ipSelected(QString ip)
{
    char localAddress[64] = {0};
    sprintf(localAddress, "tcp://%s:%d", ip.toStdString().c_str(), PORT);
    Messaging::Messages::Factory()->Register(localAddress);
    LOGINFOZ("Local address set to %s", localAddress);
    if(!m_epSrv.empty())
        m_messenger.Send(m_epSrv,
                         Messaging::Messages::Factory()->
                         MSG_HDSK(Messaging::MSG_ROLES_ENUM::CONSUMER));
}

void viewmodel::videoFetchComplete(const QString &vid)
{
    LOGINFOZ("File received as %s", vid.toStdString().c_str());
}