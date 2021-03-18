#ifndef COMMANDDATA_H
#define COMMANDDATA_H
#include "commandbase.h"

class CommandData:public CommandBase
{
public:
    CommandData(const std::string& file);
    int Run(FtpControlChannel &controlCHannel, FtpDataChannel &dataChannel) override;
};

#endif // COMMANDDATA_H
