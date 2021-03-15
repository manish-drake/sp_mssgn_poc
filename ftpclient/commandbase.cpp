#include "commandbase.h"
#include "ftpcontrolchannel.h"
#include "ftpdatachannel.h"

void CommandBase::setArgs(const std::string &args)
{
    m_args = args;
}

void CommandBase::setReply(const std::string &reply)
{
    m_reply = reply;
}

int CommandBase::run(FtpControlChannel &controlCHannel, FtpDataChannel &dataChannel)
{
    int result = 0;
    controlCHannel.command(m_cmd, m_args);
    return result;
}

CommandBase::CommandBase(const std::string& cmd):QObject(nullptr), m_cmd{cmd}, m_args{""}
{


}

int CommandBase::Run(FtpControlChannel &controlCHannel, FtpDataChannel &dataChannel)
{
    return this->run(controlCHannel, dataChannel);
}

CommandBase::~CommandBase()
{

}
