#include "viewmodel.h"
#include "messages.h"
#include <iostream>
#include "messaging_exceptions.h"
#include "logger.h"
#include "../common/network.h"



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
    m_state = 0;
}
viewmodel::viewmodel(QObject *parent) :
    QObject(parent),
    m_state{0},
    m_listener{PORT},
    m_broker{this}
{
    LOGINFO("Initializing");
    m_multListener.Start([&](std::string& broadcast){
        LOGINFO(broadcast);
    });
}

bool viewmodel::run(const int &argAction/*[0: STA, 1: STO]*/)
{
    //m_state = {0: [STA=0,STO=0], 1: [STA=1,STA=0], 2: [STA=1,STO=1]}
    bool valid = false;
    LOGINFOZ("Pressed: %d", argAction);

    switch (argAction) {
    case 0:{
        if(m_state == 0){
            auto start = Messaging::Messages::Factory()->MSG_STRT();
            //            m_messenger.Send("tcp://192.168.1.94:8284", start);
            setState(1);
            valid = true;
        }
        break;
    }
    case 1:{
        if(m_state == 1){
            auto stop = Messaging::Messages::Factory()->MSG_STOP();
            //            m_messenger.Send("tcp://192.168.1.94:8284", stop);
            setState(2);
            valid = true;
        }
        break;
    }
    case 2:{
        if(m_state == 2){
            setState(0);
            valid = true;
        }
        break;
    }
    default:
        break;
    }
    return valid;
}

void viewmodel::start()
{
    LOGINFO("Statring listener.");
    m_listener.Listen([&](const std::string &msg) {
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
