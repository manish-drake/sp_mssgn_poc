#include "viewmodel.h"
#include "messages.h"

viewmodel::viewmodel(QObject *parent) : QObject(parent), m_state{0}
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
            m_messenger.Send("", start);
            m_state = 1; valid = true;
        }
        break;
    }
    case 1:{
        if(m_state == 1){
            auto stop = Messaging::Messages::Factory()->MSG_STOP();
            m_messenger.Send("", stop);
            m_state = 2; valid = true;
        }
        break;
    }
    default:
        break;
    }
    return valid;
}
