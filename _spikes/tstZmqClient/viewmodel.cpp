#include "viewmodel.h"
#include <zmq.hpp>
ViewModel::ViewModel(QObject *parent) : QObject(parent)
{

}

void ViewModel::send()
{
    zmq::context_t ctx(1);
    zmq::socket_t sock(ctx, ZMQ_DEALER);
    sock.connect("tcp://10.21.17.37:8284");
    zmq::message_t msg("136.232.44.46:8283|203|", 24);
    sock.send(&msg, 24);
}
