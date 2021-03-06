#include "delegate.h"
#include "messages.h"
#include <iostream>
#include "logger.h"

void Messaging::Delegate::OnReceived(const std::string &argMsg)
{
    LOGINFO(argMsg.c_str());

    Messaging::Message msg = Messaging::Messages::Factory()->Parse(argMsg.c_str());
    if(msg.from.empty())
    {
        LOGWARN("The message sender is missing. Disposing of the message.");
        return;
    }
    if(!Messaging::Messages::Factory()->cmpIPAddrRange(msg.from))
    {
        LOGWARNZ("The sender %s doen not belong to the system network. Disposing of the message.", msg.from.c_str());
        return;
    }
    switch (msg.task)
    {
    case 200: //acknowledgement received for last sent message
        m_delegator->OnAcknowledgement(msg.from.c_str(), msg.args.c_str());
        break;
    case 400: //last message you sent was unknown
        m_delegator->OnException(msg.from.c_str(), msg.args.c_str());
    case 201://notification that the new video is available on server
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        m_delegator->OnNewVideoAvailable(msg.from.c_str(), msg.args.c_str());
        break;
    case 202: //request for subscription
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        m_delegator->OnSubscription(msg.from.c_str(), msg.args.c_str());
        break;
    case 203: //request for starting the recording
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        m_delegator->OnStartRecording(msg.from.c_str(), msg.args.c_str());
        break;
    case 204: //request for stopping the recording
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        m_delegator->OnStopRecording(msg.from.c_str(), msg.args.c_str());
        break;
    case 205: //notification that the video has been FTPed
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        m_delegator->OnVideoFTPComplete(msg.from.c_str(), msg.args.c_str());
        break;
    case 206: //notification that the source is idle
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        m_delegator->OnSourceIdle(msg.from.c_str(), msg.args.c_str());
        break;
    case 207: //Hand-shake with the service informing about the role
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        m_delegator->OnHandshake(msg.from.c_str(), msg.args.c_str());
        break;
    case 208: //Hand-shake with the service informing about the role
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        m_delegator->OnRequestSources(msg.from.c_str(), msg.args.c_str());
        break;
    case 209: //Hand-shake with the service informing about the role
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        m_delegator->OnReplySources(msg.from.c_str(), msg.args.c_str());
        break;
    case 210: //Hand-shake response with service assigning clientID
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_RCVD());
        m_delegator->OnHandshakeId(msg.from.c_str(), msg.args.c_str());
        break;
    default:  //unknown message
        m_messenger.Send(msg.from, Messaging::Messages::Factory()->MSG_UNKN());
        m_delegator->OnUnknownMessage(msg.from.c_str(), msg.args.c_str());
        break;
    }
}


Messaging::Delegate::Delegate(IDelegator* const delegator):m_delegator{delegator}
{

}


Messaging::Delegate::~Delegate()
{
}
