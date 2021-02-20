#include "ftpclient.h"
#include <iostream>
#include <QFile>


FTPClient::FTPClient(QObject *parent) : QObject(parent)
{
    QObject::connect(this, &FTPClient::connectToServer, &controlChannel, &FtpControlChannel::connectToServer);

}

void FTPClient::Receive(const std::string& fileName, std::function<void(const bool &)> cb)
{
    m_callback = cb;
    commands.push_back({"USER", "sportspip"});// login)
    commands.push_back({"PORT", ""}  );       // announce port for data connection, args added below.
    commands.push_back({"CWD", "videos"}  );
    commands.push_back({"RETR", "sample.mp4"} );       // send a file
    commands.push_back({"QUIT", ""} );       // send a file

    QString server = QString::fromLocal8Bit("192.168.1.166");

    int post = 0;
    // Commands to be sent

    file1.open("/home/manish/git/sp_mssgn_poc/sppad/receive.mp4", std::ios::out | std::ios::binary);
    // Print all data retrieved from the server on the console.
    QObject::connect(&dataChannel, &FtpDataChannel::dataReceived, [&](const QByteArray &data) {

        file1.write(data.constData(), data.size());
    });

    qDebug()<< "Post:" << 4;
    // Translate server replies into state machine events.
    QObject::connect(&controlChannel, &FtpControlChannel::reply,
                     [this, &cb](int code, const QString &parameters) {
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
                QString a = "drake8283";
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
                CMD = 4;
                Command command = commands.takeFirst();
                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
            }
            break;
        }
        case 4:
        {
            if(cd == "reply.2xx")
            {
                CMD = 5;

                QObject::connect(&this->dataChannel, &FtpDataChannel::remoteSocketOpen, [&](){
                    std::cout << "Socket ope!" << std::endl;
                });
                Command command = commands.takeFirst();
                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
            }
            break;
        }
        case 5:
        {
            if((cd == "reply.2xx") || (cd == "reply.4xx"))
            {
                file1.close();
                cb(true);
            }
        }
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
    emit connectToServer(0);
    qDebug()<< "Post:" << 7;

}

void FTPClient::InvokeCallback()
{
    /*
     * Messaging::Messenger m;

    m.Send("tcp://localhost:8285", Messaging::Messages::Factory()->MSG_VFTP("sample.mp4"));

*/
}

void FTPClient::Send(const QString &file, std::function<void(const std::string &)> cb)
{
    connect(this, &FTPClient::videoFTPComplete, this, &FTPClient::InvokeCallback);
    commands.push_back({"USER", "sportspip"});// login)
    commands.push_back({"PORT", ""}  );       // announce port for data connection, args added below.
    commands.push_back({"CWD", "videos"}  );
    commands.push_back({"STOR", file} );       // send a file
    commands.push_back({"QUIT", ""} );       // send a file

    QString server = QString::fromLocal8Bit("192.168.1.166");

    int post = 0;
    // Commands to be sent


    // Print all data retrieved from the server on the console.
    QObject::connect(&dataChannel, &FtpDataChannel::dataReceived, [](const QByteArray &data) {
        std::cout << data.constData();
    });

    qDebug()<< "Post:" << 4;
    // Translate server replies into state machine events.
    QObject::connect(&controlChannel, &FtpControlChannel::reply,
                     [this, &cb](int code, const QString &parameters) {
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
                QString a = "drake8283";
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
                CMD = 4;
                Command command = commands.takeFirst();
                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
            }
            break;
        }
        case 4:
        {
            if(cd == "reply.2xx")
            {
                CMD = 5;

                QObject::connect(&this->dataChannel, &FtpDataChannel::remoteSocketOpen, [&, &cb](){
                    QFile file("/home/manish/git/sample.mp4");
                    if (!file.open(QIODevice::ReadOnly)) return;
                    QByteArray blob = file.readAll();
                    dataChannel.sendData(blob);
                    dataChannel.close();
                    emit videoFTPComplete();
                });
                Command command = commands.takeFirst();
                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
            }
            break;
        }
        case 5:
        {
            if(cd == "reply.1xx")
            {
                CMD = 6;

            }
        }
            break;
        case 6:
        {
            if(cd == "reply.1xx")
            {
                CMD = 7;

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
    //controlChannel.connectToServer(server);
    emit connectToServer(0);
    qDebug()<< "Post:" << 7;
}
