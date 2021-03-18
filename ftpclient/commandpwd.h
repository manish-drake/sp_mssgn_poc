#ifndef COMMANDPWD_H
#define COMMANDPWD_H
#include "commandbase.h"

class CommandPwd:public CommandBase
{
public:
    CommandPwd(const std::string& pwd);
};

#endif // COMMANDPWD_H
