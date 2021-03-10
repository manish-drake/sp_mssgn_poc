#include "viewmodel.h"
#include "messages.h"
#include <iostream>
#include "messaging_exceptions.h"
#include "logger.h"
#include "../common/network.h"
#include "csvlist.h"



void viewmodel::OnAcknowledgement(const char *from, const char *args)
{
    LOGINFOZ("%s -ack-> %s", from, args);
}

void viewmodel::OnException(const char *from, const char *args)
{
    LOGERRZ("%s -err-> %s", from, args);
    throw Messaging::UnknownMessageException();
}

void viewmodel::OnUnknownMessage(const char *from, const char *args)
{
    LOGWARNZ("%s -ukn-> %s", from, args);
}

void viewmodel::OnSourceIdle(const char *from, const char *args)
{
    m_state = 0;
}

void viewmodel::OnReplySources(const char *from, const char *args)
{
    m_epSrcs.clear();
    if(sizeof (args) > 0)
    {
        CSVList::row list;
        CSVList::split(args, ",", &list);
        if(list.size() > 0)
        {
            m_epSrcs.insert(m_epSrcs.begin(), list.begin(), list.end());
        }
    }

    if(m_epSrcs.size() > 0) setState(1);
    emit sourecesChanged();
}
viewmodel::viewmodel(QObject *parent) :
    QObject(parent),
    m_state{0},
    m_listener{PORT},
    m_broker{this}
{
    LOGINFO("Initializing");
    m_multListener.Start([&](const std::string & serverId, const std::string &msgType, const std::string & broadcast){
        LOGINFOZ("Broadcast received %s", broadcast.c_str());

        m_epSrv = "tcp://" + broadcast + ":8285";
        if(Messaging::Messages::IsRegistered())
            m_messenger.Send(m_epSrv,
                             Messaging::Messages::Factory()->
                             MSG_HDSK(Messaging::MSG_ROLES_ENUM::CONTROLLER));
    });
}

bool viewmodel::run(const int &argAction/*[0: STA, 1: STO]*/)
{
    //m_state = {0: [STA=0,STO=0], 1: [STA=1,STA=0], 2: [STA=1,STO=1]}
    bool valid = false;
    LOGINFOZ("Pressed: %d", argAction);

    switch (argAction) {
    case 0:{
        if(m_state == 1){
            auto start = Messaging::Messages::Factory()->MSG_STRT();
            for(auto& src: m_epSrcs)
            {
                 m_messenger.Send(src, start);
            }
            setState(2);
            valid = true;
        }
        break;
    }
    case 1:{
        if(m_state == 2){
            auto stop = Messaging::Messages::Factory()->MSG_STOP();
            for(auto& src: m_epSrcs)
            {
                 m_messenger.Send(src, stop);
            }
            setState(3);
            valid = true;
        }
        break;
    }
    case 2:{
        if(m_state == 3){
            setState(0);
            valid = true;
        }
        break;
    }        
    case 100:{
        setState(0);
        m_messenger.Send(m_epSrv, Messaging::Messages::Factory()->MSG_RQSR());
        valid = true;
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
    if(!m_epSrv.empty())
        m_messenger.Send(m_epSrv,
                         Messaging::Messages::Factory()->
                         MSG_HDSK(Messaging::MSG_ROLES_ENUM::CONTROLLER));
}
