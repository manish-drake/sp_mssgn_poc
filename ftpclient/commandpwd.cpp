#include "commandpwd.h"


CommandPwd::CommandPwd(const std::string &pwd):CommandBase("PWD")
{
    this->setArgs(pwd);
    this->setReply("reply.2xx");
}
