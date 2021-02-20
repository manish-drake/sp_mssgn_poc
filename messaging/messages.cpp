#include "messages.h"
#include "csvlist.h"
#include <string.h>
#include <string>     // std::string, std::stoi
#include <sstream>

Messaging::Messages Messaging::Messages::s_singleton;


Messaging::Messages::Messages()
{
}

std::string Messaging::Messages::construct(Messaging::Message argMsg)
{
    std::stringstream ss;
    ss << argMsg.from << DLM << argMsg.task << DLM << argMsg.args;
    return ss.str();
}
Messaging::Message Messaging::Messages::Parse(const char *argMsg)
{
    CSVList::row msgParts;
    CSVList::split(argMsg, DLM, &msgParts);
    if(msgParts.size() < 3) msgParts.push_back("");

    return{
        msgParts[0],
                atoi(msgParts[1].c_str()),
                msgParts[2]
    };
}

std::string Messaging::Messages::MSG_RCVD()
{
    return construct({
                         m_endpoint,
                         200,
                         ""
                     });
}
std::string Messaging::Messages::MSG_UNKN()
{
    return construct({
                         m_endpoint,
                         400,
                         ""
                     });
}
std::string Messaging::Messages::MSG_NWVA(const char* args/*name of the new video available*/)
{
    return construct({
                         m_endpoint,
                         201,
                         args
                     });
}
std::string Messaging::Messages::MSG_SCRB(const char* args/*event*/)
{
    return construct({
                         m_endpoint,
                         202,
                         args
                     });
}

std::string Messaging::Messages::MSG_STRT()
{
    return construct({
                         m_endpoint,
                         203,
                         ""
                     });
}

std::string Messaging::Messages::MSG_STOP()
{
    return construct({
                         m_endpoint,
                         204,
                         ""
                     });
}

std::string Messaging::Messages::MSG_VFTP(const std::string &fileName)
{
    return construct({
                         m_endpoint,
                         205,
                         fileName
                     });
}

Messaging::Messages::~Messages()
{
}
