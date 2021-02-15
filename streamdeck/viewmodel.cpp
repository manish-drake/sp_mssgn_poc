#include "viewmodel.h"
#include "messages.h"
#include <iostream>

viewmodel::viewmodel(QObject *parent) :
    QObject(parent),
    m_state{0},
    m_listener{"tcp://*:8283"}
{

}

bool viewmodel::run(const int &argAction/*[0: STA, 1: STO]*/)
{
    //m_state = {0: [STA=0,STO=0], 1: [STA=1,STA=0], 2: [STA=1,STO=1]}
    bool valid = false;
    switch (argAction) {
    case 0:{
        if(m_state == 0){
            auto start = Messaging::Messages::Factory()->MSG_STRT();
            m_messenger.Send("tcp://localhost:8284", start);
            m_state = 1; valid = true;
        }
        break;
    }
    case 1:{
        if(m_state == 1){
            auto stop = Messaging::Messages::Factory()->MSG_STOP();
            m_messenger.Send("tcp://localhost:8284", stop);
            m_state = 2; valid = true;
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
    m_listener.Listen([&](const std::string &msg) {

        std::cout << "Received: " << msg << std::endl;

        m_worker.OnReceived(msg);
    });
}
