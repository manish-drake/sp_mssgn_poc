#ifndef MESSAGES_H
#define MESSAGES_H
#include <string>
#include "logger.h"
using std::string;
namespace Messaging
{

enum MSG_EVENTS_ENUM {
    NEW_VIDEO_AVAILABLE = 0,
    SRC_IDLE = 1
};
enum MSG_ROLES_ENUM {
    SOURCE = 0,
    CONSUMER = 1,
    CONTROLLER
};
struct Message
{
    std::string from;
    int task;
    std::string args;
};

class Messages
{
    const char *DLM = "|";

private:
    Messages();
    ~Messages();
    static Messages s_singleton;
    std::string m_endpoint;

private:
    std::string construct(Message argMsg);

public:
    static Messages *Factory()
    {
        return &s_singleton;
    }
    static void Register(const char *endpoint)
    {
        LOGINFOZ("Messages regitered at endpoint: %s", endpoint);
        s_singleton.m_endpoint = endpoint;
    }
    Message Parse(const char *argMsg);
    std::string MSG_RCVD();
    std::string MSG_UNKN();
    std::string MSG_NWVA(const char* args);
    std::string MSG_SCRB(const char* args);
    std::string MSG_STRT();
    std::string MSG_STOP();
    std::string MSG_VFTP(const std::string &fileName);
    std::string MSG_SRID();
    std::string MSG_HDSK(MSG_ROLES_ENUM role);
    std::string MSG_RQSR();
    std::string MSG_RPSR(const string &csvSources);
};
} // namespace Messaging
#endif //MESSAGES_H
