#ifndef FTPCLIENT_H
#define FTPCLIENT_H

#include <QObject>
#include "ftpcontrolchannel.h"
#include "ftpdatachannel.h"
#include <functional>
#include <fstream>

struct Command {
    QString cmd;
    QString args;
};
class FTPClient : public QObject
{
    Q_OBJECT
    FtpDataChannel dataChannel;
    FtpControlChannel controlChannel;
    QList<Command> commands;
    std::ofstream file1;
    std::string m_server;
public:
    explicit FTPClient(const char* server, QObject *parent = nullptr);
    void Send(const QString &file);
    void Receive(const std::string &fileName);
signals:
    void connectToServer(QString server);
    void videoFTPComplete();

public slots:
    void InvokeCallback();
};

#endif // FTPCLIENT_H
