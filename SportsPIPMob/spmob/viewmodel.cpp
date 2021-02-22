#include "delegate.h"
#include "listener.h"
#include "viewmodel.h"
#include "messaging_exceptions.h"
#include <iostream>
#include <thread>
#include "messages.h"
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
}

void viewmodel::OnStopRecording(const char *from, const char *args)
{
    static int num = 0;
    setBody("Received: Stop Recording");
    QString filename = "sample.mp4";

    //m_ftp.Send(filename, [this](const std::string& file) {
    //    m_messenger.Send("tcp://localhost:8285", Messages::Factory()->MSG_VFTP(file));
    //});
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
    m_broker{this},
    m_listener{8284}
{
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
