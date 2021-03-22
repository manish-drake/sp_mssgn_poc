#include "messages.h"
#include "csvlist.h"
#include <string.h>
#include <string>     // std::string, std::stoi
#include <sstream>
#include "../common/patch.h"

Messaging::Messages Messaging::Messages::s_singleton;


Messaging::Messages::Messages()
{
}

std::string Messaging::Messages::construct(Messaging::Message argMsg)
{
    std::stringstream ss;
    ss << argMsg.from << DLM << argMsg.task << DLM << argMsg.args ;
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

//acknowledgement received for last sent message
std::string Messaging::Messages::MSG_RCVD()
{
    return construct({
                         m_endpoint,
                         200,
                         ""
                     });
}

//last message you sent was unknown
std::string Messaging::Messages::MSG_UNKN()
{
    return construct({
                         m_endpoint,
                         400,
                         ""
                     });
}

//notification that the new video is available on server
std::string Messaging::Messages::MSG_NWVA(const char* args/*name of the new video available*/)
{
    return construct({
                         m_endpoint,
                         201,
                         args
                     });
}

//request for subscription
std::string Messaging::Messages::MSG_SCRB(const char* args/*event*/)
{
    return construct({
                         m_endpoint,
                         202,
                         args
                     });
}

//request for starting the recording
std::string Messaging::Messages::MSG_STRT()
{
    return construct({
                         m_endpoint,
                         203,
                         ""
                     });
}

//request for stopping the recording
std::string Messaging::Messages::MSG_STOP()
{
    return construct({
                         m_endpoint,
                         204,
                         ""
                     });
}

//notification that the video has been FTPed
std::string Messaging::Messages::MSG_VFTP(const std::string &fileName)
{
    return construct({
                         m_endpoint,
                         205,
                         fileName
                     });
}

//notification that the source is idle
string Messaging::Messages::MSG_SRID(const char *args)
{
    return construct({
                         m_endpoint,
                         206,
                         args
                     });
}

//Hand-shake with the service informing about the role
string Messaging::Messages::MSG_HDSK(Messaging::MSG_ROLES_ENUM role)
{
    return construct({
                         m_endpoint,
                         207,
                         patch::to_string(role)
                     });
}

string Messaging::Messages::MSG_HDID(const char* args)
{
    return construct({
                         m_endpoint,
                         207,
                         args
                     });
}

string Messaging::Messages::MSG_RQSR()
{
    return construct({
                         m_endpoint,
                         208,
                         ""
                     });
}

string Messaging::Messages::MSG_RPSR(const std::string& csvSources)
{
    return construct({
                         m_endpoint,
                         209,
                         csvSources.c_str()
                     });
}

Messaging::Messages::~Messages()
{
}
