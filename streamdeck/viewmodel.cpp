#include "viewmodel.h"
#include "messages.h"
#include <iostream>
#include "messaging_exceptions.h"
#include "logger.h"
#include "../common/network.h"
#include "csvlist.h"
#include <QTimer>



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
    setState(1);
}

void viewmodel::OnReplySources(const char *from, const char *args)
{
    m_epSrcs.clear();
    setIdent("No sources available!");
    if(sizeof (args) > 0)
    {
        CSVList::row list;
        CSVList::split(args, ",", &list);
        if(list.size() > 0)
        {
            m_epSrcs.insert(m_epSrcs.begin(), list.begin(), list.end());
            QString srcs{"Sources: "};
            srcs.append(args);
            setIdent(srcs);
            setStatus("Ready to start recording..");
        }
    }

    if(m_epSrcs.size() > 0) setState(1);
    emit sourecesChanged();
}

void viewmodel::auto_stopAfter(int secs)
{
    QTimer::singleShot(secs*1000, [&](){
        LOGINFO("Auto stopping..");
        this->run(2);
    });
}

void viewmodel::auto_startAfter(int secs)
{
    QTimer::singleShot(secs*1000, [&](){
        LOGINFO("Auto starting..");
        this->run(1);
    });
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
        setState(0);
        m_messenger.Send(m_epSrv, Messaging::Messages::Factory()->MSG_RQSR());
        setStatus("Identif sources..");
        valid = true;
        break;
    }
    case 1:{
        auto start = Messaging::Messages::Factory()->MSG_STRT();
        for(auto& src: m_epSrcs)
        {
             m_messenger.Send(src, start);
             setStatus("Recording started..");
        }
        setState(2);
        valid = true;
        auto_stopAfter(30);
        break;
    }
    case 2:{
        auto stop = Messaging::Messages::Factory()->MSG_STOP();
        for(auto& src: m_epSrcs)
        {
             m_messenger.Send(src, stop);
             setStatus("Recording stopped..");
        }
        setState(3);
        valid = true;
        auto_startAfter(2);
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
