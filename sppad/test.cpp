#include "test.h"
#include <iostream>
test::test(QObject *parent) : QObject(parent),m_val(-1), m_listener{"tcp://*:8286"}
{
}
void test::start()
{
    m_listener.Listen([&](const std::string &msg) {

        std::cout << "Received: " << msg << std::endl;

        m_worker.OnReceived(msg);
    });
}
