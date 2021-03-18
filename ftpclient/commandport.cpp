#include "commandport.h"

CommandPort::CommandPort():CommandBase("PORT")
{
    this->setReply("reply.2xx");
}

void CommandPort::SetPort(const std::string &port)
{
    this->setArgs(port);
}
