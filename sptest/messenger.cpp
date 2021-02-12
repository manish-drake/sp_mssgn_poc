#include "messenger.h"
#include <zmq.hpp>
Messaging::Messenger::Messenger()
{
}


void Messaging::Messenger::Send(const char* to, const std::string &argMsg)
{
    zmq::context_t ctx(1);
    zmq::socket_t sock(ctx, ZMQ_REQ);
    zmq::message_t msg(argMsg.begin(), argMsg.end());
    sock.connect(to);
    sock.send(msg);
}


Messaging::Messenger::~Messenger()
{
}