#include "viewmodel.h"
#include <iostream>
#include "messaging_exceptions.h"
#include "logger.h"
#include "messages.h"

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
    m_multListener.Start([&](const std::string & serverId, const std::string &msgType, const std::string & broadcast){
        LOGINFOZ("Broadcast received %s", broadcast.c_str());
        m_epSrv = "tcp://" + broadcast + ":8285";
        if(Messaging::Messages::IsRegistered())
            m_messenger.Send(m_epSrv,
                             Messaging::Messages::Factory()->
                             MSG_HDSK(Messaging::MSG_ROLES_ENUM::CONSUMER));
    });
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
