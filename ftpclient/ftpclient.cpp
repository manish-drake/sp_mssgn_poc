#include "ftpclient.h"
#include <iostream>
#include <QFile>
#include <QFileInfo>
#include "logger.h"

FTPClient::FTPClient(QObject *parent)
{
    QObject::connect(this, &FTPClient::connectToServer, &controlChannel, &FtpControlChannel::connectToServer);
    LOGINFO("FTP client initialized");
}


void FTPClient::Receive(const std::string& fileName, const QString &server)
{
    LOGINFO("Receiving file");
    commands.push_back({"USER", "sportspip"});// login)
    commands.push_back({"PORT", ""}  );       // announce port for data connection, args added below.
    commands.push_back({"CWD", "videos"}  );
    commands.push_back({"RETR", fileName.c_str()} );       // send a file
    commands.push_back({"QUIT", ""} );       // send a file



    int post = 0;
    // Commands to be sent

    file1.open("/home/manish/git/sp_mssgn_poc/sppad/receive.mp4", std::ios::out | std::ios::binary);
    // Print all data retrieved from the server on the console.
    QObject::connect(&dataChannel, &FtpDataChannel::dataReceived, [&](const QByteArray &data) {
        LOGINFO("Received data...");
        file1.write(data.constData(), data.size());
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
    emit connectToServer(server);
    qDebug()<< "Post:" << 7;

}

void FTPClient::InvokeCallback()
{
    /*
     * Messaging::Messenger m;

    m.Send("tcp://localhost:8285", Messaging::Messages::Factory()->MSG_VFTP("sample.mp4"));

*/
}

void FTPClient::Send(const QString &fileName, const QString &server)
{
    LOGINFO("Sending file " + fileName.toLatin1());
    m_fileName = fileName;
    QFileInfo fInfo(m_fileName);
    QString bname = fInfo.baseName();
    QString fname = bname.append(".").append(fInfo.completeSuffix());
    connect(this, &FTPClient::videoFTPComplete, this, &FTPClient::InvokeCallback);
    commands.push_back({"OPTS", "UTF8 ON"});// login)
    commands.push_back({"USER", "sportspip"});// login)
    commands.push_back({"PORT", ""}  );       // announce port for data connection, args added below.
//    commands.push_back({"CWD", "videos"}  );
    commands.push_back({"STOR", fname} );       // send a file
    commands.push_back({"QUIT", ""} );       // send a file

    // Commands to be sent


    // Print all data retrieved from the server on the console.
    QObject::connect(&dataChannel, &FtpDataChannel::dataReceived, [](const QByteArray &data) {
        LOGINFO("Received data...");
        std::cout << data.constData();
    });

    qDebug()<< "Post:" << 4;
    // Translate server replies into state machine events.
    QObject::connect(&controlChannel, &FtpControlChannel::reply,
                     [this, &fileName, &fname](int code, const QString &parameters) {
        static int CMD = -1;
        auto cd = QString("reply.%1xx").arg(code / 100);
        qDebug() << "Code: " << cd;
        switch (CMD) {
        case -1:
        {
            if(cd == "reply.2xx")
            {
                CMD = 0;
                Command command = commands.takeFirst();
                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
            }
            break;
        }
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
//        case 3:
//        {
//            if(cd == "reply.2xx")
//            {
//                CMD = 4;
//                Command command = commands.takeFirst();
//                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
//            }
//            break;
//        }
        case 3:
        {
            if(cd == "reply.2xx")
            {
                CMD = 4;

                QObject::connect(&this->dataChannel, &FtpDataChannel::remoteSocketOpen, [&](){
//                    QFile file(fileName);
//                    if (!file.open(QIODevice::ReadOnly)) return;
//                    QByteArray blob = file.readAll();
//                    dataChannel.sendData(blob);
//                    dataChannel.close();
//                    emit videoFTPComplete();
                    std::cout << "Data channel open" << std::endl;
                });
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
                std::cout << "Sending file now" << std::endl;
                QFile file(m_fileName);
                if (!file.open(QIODevice::ReadOnly)) return;
                QByteArray blob = file.readAll();
                dataChannel.sendData(blob);
                dataChannel.close();
                emit videoFTPComplete(fname);
            }
        }
            break;
        case 5:
        {
            if(cd == "reply.1xx")
            {
                CMD = 6;

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
        commands[2].args = dataChannel.portspec();
    });

    qDebug()<< "Post:" << 6;
    // Connect to our own local FTP server
    //controlChannel.connectToServer(QString::fromStdString(m_server));
    emit connectToServer(server);
    qDebug()<< "Post:" << 7;
}
