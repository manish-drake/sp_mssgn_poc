#ifndef MESSAGES_H
#define MESSAGES_H
#include <string>
using std::string;
namespace Messaging
{
    struct Message
    {
        const char *from;
        int task;
        const char *args;
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
            s_singleton.m_endpoint = endpoint;
        }
        Message Parse(const char *argMsg);
        std::string MSG_RCVD();
        std::string MSG_UNKN();
        std::string MSG_NWVA(const char* args);
        std::string MSG_SCRB(const char* args);
        std::string MSG_STRT();
        std::string MSG_STOP();
    };
} // namespace Messaging
#endif //MESSAGES_H