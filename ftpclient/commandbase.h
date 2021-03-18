#ifndef COMMAND_H
#define COMMAND_H
#include <iostream>
#include <initializer_list>
#include <vector>
#include <QObject>

class FtpControlChannel;
class FtpDataChannel;
class CommandBase: public QObject
{
    std::string m_cmd, m_args, m_reply;
protected:
    void setArgs(const std::string& args);
    void setReply(const std::string& reply);
    int run(FtpControlChannel &controlCHannel, FtpDataChannel &dataChannel);
    std::string args() const
    {
        return m_args;
    }
public:
    CommandBase(const std::string& cmd);
    virtual int Run(FtpControlChannel &controlCHannel, FtpDataChannel &dataChannel);
    std::string ExpectedReply() const
    {
        return m_reply;
    }
    virtual ~CommandBase();
};

#endif // COMMAND_H
