#ifndef FTPCLIENT_H
#define FTPCLIENT_H

#include <QObject>
#include "ftpcontrolchannel.h"
#include "ftpdatachannel.h"
#include <functional>
#include <fstream>
#include "pipeline.h"
#include <thread>
#include <memory>
#include <mutex>
#include <condition_variable>


class FTPClient : public QObject
{
    Q_OBJECT
    FtpDataChannel dataChannel;
    FtpControlChannel controlChannel;
    bool m_isConnected;
    Pipeline m_pipeline;
    bool isConnected() const
    {
        return m_isConnected;
    }
    std::mutex m_mtx;
    std::condition_variable m_cv;
    std::unique_ptr<std::thread> m_pth;
    void send_worker(const QString &fileName, const QString &server);
public:
    explicit FTPClient(QObject *parent = nullptr);
    void Send(const QString &file, const QString &server);
    void Fetch(const std::string &fileName, const QString &server, const std::string &mediaFolder);
    ~FTPClient();
signals:
    void connectToServer(QString server);
    void videoFTPComplete(const QString& vid);
    void videoFetchComplete(const QString& vid);

};

#endif // FTPCLIENT_H
