#ifndef COMMANDPORT_H
#define COMMANDPORT_H
#include "commandbase.h"

class CommandPort: public CommandBase
{
public:
    CommandPort();
    void SetPort(const std::string& port);
};

#endif // COMMANDPORT_H
