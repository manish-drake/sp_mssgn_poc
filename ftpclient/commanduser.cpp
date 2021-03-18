#include "commanduser.h"


CommandUser::CommandUser(const std::string &uname):CommandBase("USER")
{
    this->setArgs(uname);
    setReply("reply.3xx");
}
