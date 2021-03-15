#ifndef COMMANDOPTS_H
#define COMMANDOPTS_H
#include "commandbase.h"
#include <initializer_list>
#include <vector>

class CommandOpts: public CommandBase
{
    std::vector<std::string> m_optoins;
public:
    CommandOpts(std::initializer_list<std::string> options);
    int Run(FtpControlChannel &controlCHannel, FtpDataChannel &dataChannel) override;
};

#endif // COMMANDOPTS_H
