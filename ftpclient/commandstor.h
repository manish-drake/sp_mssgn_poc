#ifndef COMMANDSTOR_H
#define COMMANDSTOR_H
#include "commandbase.h"

class CommandStor:public CommandBase
{
public:
    CommandStor(const std::string& name);
};

#endif // COMMANDSTOR_H
