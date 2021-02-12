#include "messages.h"
#include "csvlist.h"
#include <cstring>
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
    return{
        msgParts[0].c_str(),
        std::stoi(msgParts[1].c_str()),
        msgParts[2].c_str()
        };
}

std::string Messaging::Messages::MSG_RCVD()
{
    return construct({
        m_endpoint.c_str(),
        200,
        ""
    });
}
std::string Messaging::Messages::MSG_UNKN()
{
    return construct({
        m_endpoint.c_str(),
        400,
        ""
    });
}
std::string Messaging::Messages::MSG_NWVA(const char* args/*name of the new video available*/)
{
    return construct({
        m_endpoint.c_str(),
        201,
        args
    });
}
std::string Messaging::Messages::MSG_SCRB(const char* args/*event*/)
{
    return construct({
        m_endpoint.c_str(),
        202,
        args
    });
}

Messaging::Messages::~Messages()
{
}