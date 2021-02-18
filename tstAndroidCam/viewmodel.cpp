#include "viewmodel.h"
#include <thread>
#include <zmq.hpp>
#include <iostream>

ViewModel::ViewModel(QObject *parent) : QObject(parent)
{

}

void ViewModel::start()
{
    std::thread t([&](){
        zmq::context_t ctx(1);
        zmq::socket_t sock(ctx, ZMQ_ROUTER);

        sock.bind("tcp://*:9001");

        while(1)
        {
            zmq::message_t msg;
            sock.recv(&msg);
            sock.recv(&msg);

            std::cout << (char*)msg.data() << std::endl;
            if(blSt)
            {
                blSt = false;
                m_state = 1;
            }
            else{
                blSt = true;
                m_state = 0;
            }
            emit stateChanged(m_state);
        }

    });
    t.detach();
}
