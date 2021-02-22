#ifndef CLIENT_H
#define CLIENT_H
#include "ftpcontrolchannel.h"
#include "ftpdatachannel.h"

struct Command {
    std::string cmd;
    std::string args;
};
class client
{
    FtpControlChannel m_controlChannel;
    FtpDataChannel m_dataChannel;
public:
    client();
    int Send(const char* server, const char* file, const char* user, const char* pwd);
    int Receive(const char* server, const char* file, const char* user, const char* pwd);
};

#endif // CLIENT_H
