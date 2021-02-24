#include "worker.h"
#include "messages.h"
#include "messaging_exceptions.h"
#include <cstring>

void Worker::OnAcknowledgement(const char *from, const char *args)
{
}

void Worker::OnException(const char *from, const char *args)
{

    throw Messaging::UnknownMessageException();
}

void Worker::OnNewVideoAvailable(const char *from, const char *args)
{
}

void Worker::OnSubscription(const char *from, const char *args)
{
    auto event = std::stoi(args);
    m_subscriptions[static_cast<MSG_EVENTS_ENUM>(event)].push_back(from);
}

void Worker::OnStartRecording(const char *from, const char *args)
{
}

void Worker::OnStopRecording(const char *from, const char *args)
{
}

void Worker::OnVideoFTPComplete(const char *from, const char *args)
{
    m_messenger.Send("tcp://localhost:8286", Messaging::Messages::Factory()->MSG_NWVA(args));
    return;

    for (auto &subscriber : m_subscriptions[MSG_EVENTS_ENUM::NEW_VIDEO_AVAILABLE])
    {
        m_messenger.Send(subscriber.c_str(), Messaging::Messages::Factory()->MSG_NWVA(args));
    }
}

void Worker::OnUnknownMessage(const char *from, const char *args)
{
}
Worker::Worker()
{
}

Worker::~Worker()
{
}