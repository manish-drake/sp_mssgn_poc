#include "delegate.h"
#include "listener.h"
#include "viewmodel.h"
#include <iostream>
//#include <zmq.hpp>
#include <iostream>
#include <QFile>
#include <thread>
using namespace Messaging;
viewmodel::viewmodel(QObject *parent) : QObject(parent)
{

    commands.push_back({"USER", "manish"});// login)
    commands.push_back({"PORT", ""}  );       // announce port for data connection, args added below.
    commands.push_back({"STOR", "sample.mp4"} );       // send a file





}

viewmodel::~viewmodel()
{
    this->m_close = true;
    m_listener.Close();
}
void viewmodel::send()
{

    //    zmq::context_t ctx(1);
    //    zmq::message_t msgs("Hello World\n", 12);
    //    zmq::socket_t sock(ctx, ZMQ_REQ);
    //    sock.connect("tcp://192.168.10.7:8283");
    //    sock.send(msgs);

    //    zmq::message_t msgr(1024);
    //    sock.recv(&msgr);
    //    std::cout << msgr.data() << std::endl;
}

void viewmodel::ftp()
{
    QString server = QString::fromLocal8Bit("192.168.10.8");
    QString file = QString::fromLocal8Bit("oneplus");

    int post = 0;
    qDebug()<< "Post:" << 1;
    qDebug()<< "Post:" << 2;

    // Commands to be sent


    qDebug()<< "Post:" << 3;
    // Print all data retrieved from the server on the console.
    QObject::connect(&dataChannel, &FtpDataChannel::dataReceived, [](const QByteArray &data) {
        std::cout << data.constData();
    });

    qDebug()<< "Post:" << 4;
    // Translate server replies into state machine events.
    QObject::connect(&controlChannel, &FtpControlChannel::reply,
                     [this](int code, const QString &parameters) {
        static int CMD = 0;
        auto cd = QString("reply.%1xx").arg(code / 100);
        qDebug() << "Code: " << cd;
        switch (CMD) {
        case 0:
        {
            if(cd == "reply.2xx")
            {
                CMD = 1;
                Command command = commands.takeFirst();
                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
            }
            break;
        }
        case 1:
        {
            if(cd == "reply.3xx")
            {
                CMD = 2;
                QString c = "PASS";
                QString a = "abc@123";
                controlChannel.command(c.toLatin1(), a.toUtf8());
            }
            break;
        }
        case 2:
        {
            if(cd == "reply.2xx")
            {
                CMD = 3;
                Command command = commands.takeFirst();
                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
            }
            break;
        }
        case 3:
        {
            if(cd == "reply.2xx")
            {
                QObject::connect(&this->dataChannel, &FtpDataChannel::remoteSocketOpen, [&](){
                    QFile file(":/sample.mp4");
                    if (!file.open(QIODevice::ReadOnly)) return;
                    QByteArray blob = file.readAll();
                    dataChannel.sendData(blob);
                });
                CMD = 4;
                Command command = commands.takeFirst();
                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
            }
            break;
        }
        case 4:
        {
            if(cd == "reply.1xx")
            {
                CMD = 5;

                QObject::connect(&this->dataChannel, &FtpDataChannel::remoteSocketOpen, [&](){
                    QFile file("qrc:/sample.mp4");
                    if (!file.open(QIODevice::ReadOnly)) return;
                    QByteArray blob = file.readAll();
                    dataChannel.sendData(blob);
                });
            }
        }
            break;
        default:
            break;
        }

        //        ftpClient.submitEvent(QString("reply.%1xx").arg(code / 100), parameters);
    });

    qDebug()<< "Post:" << 5;
    QObject::connect(&controlChannel, &FtpControlChannel::opened,
                     [this](const QHostAddress &address, int) {
        dataChannel.listen(address);
        commands[1].args = dataChannel.portspec();
    });
    qDebug()<< "Post:" << 6;
    // Connect to our own local FTP server
    controlChannel.connectToServer(server);
    qDebug()<< "Post:" << 7;
}

void viewmodel::start()
{


    m_listener.Connect([&](const std::string &msg) {
        std::cout << "Received: " << msg << std::endl;
        m_worker.Received(msg);
    });

    std::thread tprime([this]() {
        while (!m_close)
        {
            m_listener.Listen();
        }
    });

    tprime.detach();
}
