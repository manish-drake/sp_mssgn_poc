#include "commandquit.h"

CommandQuit::CommandQuit():CommandBase{"QUIT"}
{
    this->setReply("reply.2xx");
}
