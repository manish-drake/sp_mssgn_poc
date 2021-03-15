#ifndef COMMANDUSER_H
#define COMMANDUSER_H
#include "commandbase.h"

class CommandUser: public CommandBase
{
public:
    CommandUser(const std::string& uname);
};

#endif // COMMANDUSER_H
