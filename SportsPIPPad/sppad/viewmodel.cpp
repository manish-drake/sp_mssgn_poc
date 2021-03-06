#include "viewmodel.h"
#include <iostream>
#include "messaging_exceptions.h"
#include "logger.h"
#include "messages.h"

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
    LOGERRZ("%d>> %s", from, args);
    /*
    m_ftp.Receive(args, [](const bool& completedOkay)
    {
        std::cout << "Video fetch status: " << completedOkay << std::endl;
    });

*/
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

void viewmodel::OnSourceIdle(const char *from, const char *args)
{

}
viewmodel::viewmodel(QObject *parent) :
    QObject(parent),
    m_val(-1),
    m_listener{PORT},
    m_broker{this},
    m_ftp("192.168.1.5")
{

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
}
