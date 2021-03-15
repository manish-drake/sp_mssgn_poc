#include "commandstor.h"

CommandStor::CommandStor(const std::string &name):CommandBase{"STOR"}
{
    this->setArgs(name);
    this->setReply("reply.1xx");
}
