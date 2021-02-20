#include "viewmodel.h"
#include <zmq.hpp>
ViewModel::ViewModel(QObject *parent) : QObject(parent)
{

}

void ViewModel::send()
{
    zmq::context_t ctx(1);
    zmq::socket_t sock(ctx, ZMQ_DEALER);
    sock.connect("tcp://192.168.10.4:9001");
    zmq::message_t msg("hello world", 12);
    sock.send(&msg, 12);
}
