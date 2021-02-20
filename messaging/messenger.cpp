#include "messenger.h"
#include <zmq.hpp>
Messaging::Messenger::Messenger()
{
}


void Messaging::Messenger::Send(std::string to, const std::string &argMsg)
{
    zmq::context_t ctx(1);
    zmq::socket_t sock(ctx, ZMQ_DEALER);
    zmq::message_t msg(argMsg.begin(), argMsg.end());
    sock.connect(to.c_str());
    sock.send(msg);
}


Messaging::Messenger::~Messenger()
{
}
