#include "ftpclient.h"
#include <iostream>
#include <QFile>
#include <QFileInfo>
#include "logger.h"
#include "commanddata.h"
#include "commandopts.h"
#include "commandport.h"
#include "commandpwd.h"
#include "commandquit.h"
#include "commandstor.h"
#include "commanduser.h"
#include <functional>


void FTPClient::send_worker(const QString &fileName, const QString &server)
{
    std::unique_lock<std::mutex> lock(m_mtx);
//    QTcpSocket socket;

//    connect(&socket, &QTcpSocket::connected, [&socket](){
//        std::cout << "connected" << std::endl;
//    });
//    socket.connectToHost("192.168.10.10", 21);

        FtpDataChannel dataChannel;
        FtpControlChannel controlChannel;
        Pipeline m_pipeline{controlChannel, dataChannel};

    ////    QObject::connect(this, &FTPClient::connectToServer, &controlChannel, &FtpControlChannel::connectToServer);

    //    LOGINFO("Sending file " + fileName.toLatin1());

    //    QFileInfo fInfo(fileName);
    //    QString bname = fInfo.baseName();
    //    QString fname = bname.append(".").append(fInfo.completeSuffix());

    //    QObject::connect(&dataChannel, &FtpDataChannel::dataReceived, [](const QByteArray &data) {
    //        LOGINFO("Received data...");
    //    });

    //    m_pipeline.Add(PipeCmd(new CommandOpts({"UTF8 ON"})))
    //            ->Add(PipeCmd(new CommandUser("sportspip")))
    //            ->Add(PipeCmd(new CommandPwd("drake8283")))
    //            ->Add(PipeCmd(new CommandPort()))
    //            ->Add(PipeCmd(new CommandStor(fname.toStdString())))
    //            ->Add(PipeCmd(new CommandData(fileName.toStdString())))
    //            ->Add(PipeCmd(new CommandQuit()));

    //    QObject::connect(&controlChannel, &FtpControlChannel::reply,
    //                     [&](int code, const QString &parameters) {
    //        auto cd = QString("reply.%1xx").arg(code / 100);
    //        auto result = m_pipeline.Process(cd);
    //        if(result != 0)
    //            m_cv.notify_one();
    //    });

    //    QObject::connect(&controlChannel, &FtpControlChannel::opened,
    //                     [this, &dataChannel, &m_pipeline](const QHostAddress &address, int) {
    //        dataChannel.listen(address);
    //        auto portCmd= m_pipeline.at(3);
    //        static_pointer_cast<CommandPort>(*portCmd)->SetPort(dataChannel.portspec().toStdString());
    //        m_isConnected = true;
    //    });

    ////    emit connectToServer(server);
        controlChannel.connectToServer("192.168.10.10");
    m_cv.wait(lock);
    std::cout << "lock released" << std::endl;
}

FTPClient::FTPClient(QObject *parent):
    m_isConnected{false}
{
    LOGINFO("FTP client initialized");
}





void FTPClient::Send(const QString &fileName, const QString &server)
{
    m_th = std::thread(std::bind(&FTPClient::send_worker, this, fileName, server));
}

void FTPClient::Fetch(const string &fileName, const QString &server, const string &mediaFolder)
{

}

FTPClient::~FTPClient()
{
    if ((m_th.joinable()))
    {
        m_th.join();
    }
}
