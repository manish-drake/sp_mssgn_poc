#include "ftpclient.h"
#include <iostream>
#include <QFile>
#include <QFileInfo>
#include "logger.h"


FTPClient::FTPClient(QObject *parent):m_isConnected{false}
{
    QObject::connect(this, &FTPClient::connectToServer, &controlChannel, &FtpControlChannel::connectToServer);
    LOGINFO("FTP client initialized");
}


void FTPClient::Fetch(const std::string& fileName, const QString &server, const std::string& mediaFolder)
{
    LOGINFO("Receiving file");
    commands.push_back({"OPTS", "UTF8 ON"});// login)
    commands.push_back({"USER", "sportspip"});// login)
    commands.push_back({"PORT", ""}  );       // announce port for data connection, args added below.
    //    commands.push_back({"CWD", "videos"}  );
    commands.push_back({"RETR", fileName.c_str()} );       // send a file
    commands.push_back({"QUIT", ""} );       // send a file



    // Commands to be sent
    std::string filePath = mediaFolder + "/" + fileName;
    LOGINFOZ("Opening file at %s", filePath.c_str());

    file1.open(filePath, std::ios::out | std::ios::binary);
    // Print all data retrieved from the server on the console.
    QObject::connect(&dataChannel, &FtpDataChannel::dataReceived, [&](const QByteArray &data) {
        LOGINFO("Received data...");
        file1.write(data.constData(), data.size());
    });

    qDebug()<< "Post:" << 4;
    // Translate server replies into state machine events.
    QObject::connect(&controlChannel, &FtpControlChannel::reply,
                     [this](int code, const QString &parameters) {
        static int CMDF = -1;
        auto cd = QString("reply.%1xx").arg(code / 100);
        qDebug() << "Code: " << cd;
        switch (CMDF) {
        case -1:
        {
            if(cd == "reply.2xx")
            {
                CMDF = 0;
                Command command = commands.takeFirst();
                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
            }
            break;
        }
        case 0:
        {
            if(cd == "reply.2xx")
            {
                CMDF = 1;
                Command command = commands.takeFirst();
                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
            }
            break;
        }
        case 1:
        {
            if(cd == "reply.3xx")
            {
                CMDF = 2;
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
                CMDF = 3;
                Command command = commands.takeFirst();
                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
            }
            break;
        }
            //        case 3:
            //        {
            //            if(cd == "reply.2xx")
            //            {
            //                CMDF = 4;
            //                Command command = commands.takeFirst();
            //                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
            //            }
            //            break;
            //        }
        case 3:
        {
            if(cd == "reply.2xx")
            {
                CMDF = 4;

                QObject::connect(&this->dataChannel, &FtpDataChannel::remoteSocketOpen, [&](){
                    std::cout << "Socket open!" << std::endl;
                });
                Command command = commands.takeFirst();
                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
            }
            break;
        }
        case 4:
        {
            if((cd == "reply.2xx") || (cd == "reply.4xx"))
            {
                LOGINFOZ("Fetch complete with %s. Closing File..", cd.toStdString().c_str());
                file1.close();
                Command command = commands.takeFirst();
                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
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

    // Print all data retrieved from the server on the console.
    QObject::connect(&dataChannel, &FtpDataChannel::dataReceived, [](const QByteArray &data) {
        LOGINFO("Received data...");
        std::cout << data.constData();
    });

    qDebug()<< "Post:" << 4;
    // Translate server replies into state machine events.
    QObject::connect(&controlChannel, &FtpControlChannel::reply,
                     [this, fileName, fname](int code, const QString &parameters) {

        auto cd = QString("reply.%1xx").arg(code / 100);
        qDebug() << "Code: " << cd;
        switch (commands.size()) {
        case 5:
        {
            if(cd == "reply.2xx")
            {
                Command command = commands.takeFirst();
                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
            }
            break;
        }
        case 4:
        {
            if(cd == "reply.2xx")
            {
                Command command = commands.takeFirst();
                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
            }
            break;
        }
        case 3:
        {
            if(cd == "reply.2xx")
            {
                Command command = commands.takeFirst();
                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
            }
            else if(cd == "reply.3xx")
            {
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
                QObject::connect(&this->dataChannel, &FtpDataChannel::remoteSocketOpen, [&](){
                    LOGINFO("Data channel open");
                });
                Command command = commands.takeFirst();
                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
            }
            break;
        }
        case 1:
        {
            if(cd == "reply.1xx")
            {
                std::cout << "Sending file now" << std::endl;
                QFile file(m_fileName);
                if (!file.open(QIODevice::ReadOnly)) return;
                QByteArray blob = file.readAll();
                dataChannel.sendData(blob);
                dataChannel.close();
                LOGINFOZ("FTP complete %s", fname.toStdString().c_str());
                emit videoFTPComplete(fname);
            }
            else  if((isConnected()) && (cd == "reply.2xx"))
            {
                LOGINFO("Transfer complete.");
                Command command = commands.takeFirst();
                m_isConnected = false;
                controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
            }
            else {
                LOGERRZ("Error transferring the file, %s", cd.toStdString().c_str());
            }
        }
        case 0:
            {
                if(cd == "reply.1xx")
                {
                    
                }
            break;
        }
        default:
            break;
        }

    });

    qDebug()<< "Post:" << 5;
    QObject::connect(&controlChannel, &FtpControlChannel::opened,
                     [this](const QHostAddress &address, int) {
        dataChannel.listen(address);
        m_isConnected = true;
        commands[2].args = dataChannel.portspec();
    });
    if(!isConnected())
    {

        /*5*/commands.push_back({"OPTS", "UTF8 ON"});// login)
        /*4*/commands.push_back({"USER", "sportspip"});// login)
        /*3*/commands.push_back({"PORT", ""}  );
        /*2*/commands.push_back({"STOR", fname} );       // send a file
        /*1*/commands.push_back({"QUIT", ""} );       // send a file

        emit connectToServer(server);
    }
    else{
        /*2*/commands.push_back({"STOR", fname} );       // send a file
        Command command = commands.takeFirst();
        controlChannel.command(command.cmd.toLatin1(), command.args.toUtf8());
    }
}
