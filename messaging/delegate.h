#ifndef DELEGATE_H
#define DELEGATE_H
#include <string>
#include "messenger.h"
#include "idelegator.h"



using std::string;

namespace Messaging
{
class  Delegate
{
private:
    Messenger m_messenger;
private:
    IDelegator * const m_delegator;
public:
    void OnReceived(const std::string &argMsg);
    Delegate(IDelegator * const delegator);


    ~Delegate();
};
} // namespace Messaging
#endif //DELEGATE_H
