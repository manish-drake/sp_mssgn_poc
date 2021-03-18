#include "commandopts.h"
#include <algorithm>
#include "ftpcontrolchannel.h"
#include "ftpdatachannel.h"

CommandOpts::CommandOpts(std::initializer_list<std::string> options):CommandBase{"OPTS"}, m_optoins{options}
{
    this->setReply("reply.2xx");
}

int CommandOpts::Run(FtpControlChannel &controlCHannel, FtpDataChannel &dataChannel)
{
    int result = 0;
    for(auto& opt: m_optoins)
    {
        setArgs(opt);
        result = std::max(result, this->run(controlCHannel, dataChannel));
    }
    return result;
}
