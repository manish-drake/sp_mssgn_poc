#include "worker.h"
#include "messages.h"
#include "messaging_exceptions.h"
#include <cstring>
#include "logger.h"
#include <algorithm>


const char* MsgRoleStr(Messaging::MSG_ROLES_ENUM role)
{
    static char* roles[] = {"Source", "Consumer", "Controller"};
    return roles[role];
}

void Worker::OnAcknowledgement(const char *from, const char *args)
{
}

void Worker::OnException(const char *from, const char *args)
{
    LOGERRZ("%d>> %s", from, args);
    throw Messaging::UnknownMessageException();
}

void Worker::OnNewVideoAvailable(const char *from, const char *args)
{
}

void Worker::OnSubscription(const char *from, const char *args)
{
    LOGINFOZ("Adding %s for event: %d", from, args);
    auto event = std::stoi(args);
}

void Worker::OnStartRecording(const char *from, const char *args)
{
    
}

void Worker::OnStopRecording(const char *from, const char *args)
{
}

void Worker::OnVideoFTPComplete(const char *from, const char *args)
{
    LOGINFO("Sending notifcation to all subscribers...");

    m_messenger.Send("tcp://localhost:8286", Messaging::Messages::Factory()->MSG_NWVA(args));
}

void Worker::OnUnknownMessage(const char *from, const char *args)
{
}

void Worker::OnSourceIdle(const char *from, const char *args)
{
}

void Worker::OnHandshake(const char *from, const char *args)
{
    auto roleVal = atoi(args);
    auto role = static_cast<Messaging::MSG_ROLES_ENUM>(roleVal);
    auto& list = m_subscribers[role];
    auto subscriber = std::string(from);
    auto it = std::find(list.begin(), list.end(), subscriber);
    if(it == list.end())
    {
        list.push_back(subscriber);
        LOGINFOZ("%s added to the role %s", from, MsgRoleStr(role));
    }
}

void Worker::OnRequestSources(const char *from, const char *args)
{
    std::string csvSources;
    auto& list = m_subscribers[Messaging::MSG_ROLES_ENUM::SOURCE];
    for(auto& src: list)
    {
        csvSources += src + ",";
    }
    m_messenger.Send(from, csvSources);
}

void Worker::OnReplySources(const char *from, const char *args)
{

}
Worker::Worker()
{
}

Worker::~Worker()
{
}
