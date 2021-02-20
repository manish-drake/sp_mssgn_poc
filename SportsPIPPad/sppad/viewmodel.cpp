#include "viewmodel.h"
#include <iostream>
#include "messaging_exceptions.h"

void viewmodel::OnAcknowledgement(const char *from, const char *args)
{

}

void viewmodel::OnException(const char *from, const char *args)
{
    throw Messaging::UnknownMessageException();
}

void viewmodel::OnNewVideoAvailable(const char *from, const char *args)
{
    m_ftp.Receive(args, [](const bool& completedOkay)
    {
        std::cout << "Video fetch status: " << completedOkay << std::endl;
    });
}

void viewmodel::OnSubscription(const char *from, const char *args)
{

}

void viewmodel::OnStartRecording(const char *from, const char *args)
{

}

void viewmodel::OnStopRecording(const char *from, const char *args)
{

}

void viewmodel::OnVideoFTPComplete(const char *from, const char *args)
{

}

void viewmodel::OnUnknownMessage(const char *from, const char *args)
{

}
viewmodel::viewmodel(QObject *parent) :
    QObject(parent),
    m_val(-1),
    m_listener{8286},
    m_broker{this}
{
}

void viewmodel::start()
{
    m_listener.Listen([&](const std::string &msg) {

        std::cout << "Received: " << msg << std::endl;

        m_broker.OnReceived(msg);
    });
}
