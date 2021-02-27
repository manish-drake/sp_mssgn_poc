#include "delegate.h"
#include "listener.h"
#include "viewmodel.h"
#include "messaging_exceptions.h"
#include <iostream>
#include <thread>
#include "messages.h"
#include <QStandardPaths>
#include <QDir>



using namespace Messaging;
void viewmodel::OnAcknowledgement(const char *from, const char *args)
{

}

void viewmodel::OnException(const char *from, const char *args)
{

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
    setBody("Received: Start Recording");
    setIsRecording(true);
}

void viewmodel::OnStopRecording(const char *from, const char *args)
{
    static int num = 0;
    setBody("Received: Stop Recording");
    QString filename = "sample.mp4";
    setIsRecording(false);

    setBody("File found");
    m_ftp.Send(m_fileName);
}

void viewmodel::OnVideoFTPComplete(const char *from, const char *args)
{

}

void viewmodel::OnUnknownMessage(const char *from, const char *args)
{

}

viewmodel::viewmodel(QObject *parent) :
    QObject(parent),
    m_header{""},
    m_body{""},
    m_footer{""},
    m_isRecording{false},
    m_broker{this},
    m_listener{8284},
    m_ftp{"192.168.1.2"}
{    
    QString localPath = QStandardPaths::writableLocation( QStandardPaths::MoviesLocation );
    QString appMediaFolder = localPath.append("/SportsPIP/Videos");
    QDir dAppMediaFolder(appMediaFolder);
    if (!dAppMediaFolder.exists()) {
        dAppMediaFolder.mkpath(".");
    }
    m_fileName = appMediaFolder.append("/video1.mp4");
}

viewmodel::~viewmodel()
{
    this->m_close = true;
}

void viewmodel::start()
{
    Messages::Factory()->Register("tcp://192.168.1.3:8284");
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
