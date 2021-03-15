#include "pipeline.h"

PipeCmd *Pipeline::getNextCommand()
{
    if(m_currentIndex < m_commands.size())
    {
        auto &cmd = m_commands[m_currentIndex];
        m_expextedReply = QString::fromStdString(cmd->ExpectedReply());
        m_currentIndex += 1;
        return  &cmd;
    }
    else{
        return nullptr;
    }
}

QString Pipeline::getExpectedReply()
{

}

Pipeline::Pipeline(FtpControlChannel &controlChannel, FtpDataChannel &dataChannel, QObject *parent)
    :QObject(parent),
      m_controlChannel{controlChannel},
      m_dataChannel{dataChannel},
      m_currentIndex{0},
      m_expextedReply{"reply.2xx"}
{

}

Pipeline *Pipeline::Add(const PipeCmd &cmd)
{
    m_commands.push_back(std::move(cmd));
    return this;
}

int Pipeline::Process(const QString &lastReply)
{
    if(lastReply == getExpectedReply())
    {
        auto cmd = getNextCommand();
        if(cmd)
        {
            return (*cmd)->Run(m_controlChannel, m_dataChannel);
        }
        else {
            return -2;
        }
    }
    else {
        return -1;
    }
}

PipeCmd *Pipeline::at(int index)
{
    if((index < m_commands.size()) && (index >= 0))
        return &m_commands[index];
    else
        return nullptr;
}
