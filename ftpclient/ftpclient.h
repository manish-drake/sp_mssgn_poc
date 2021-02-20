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
    std::function<void(const bool &)> m_callback;
public:
    explicit FTPClient(QObject *parent = nullptr);
    void Send(const QString &file, std::function<void(const std::string &)> cb);
    void Receive(const std::string &fileName, std::function<void(const bool& completedOkay)> cb);
signals:
    void connectToServer(int server);
    void videoFTPComplete();

public slots:
    void InvokeCallback();
};

#endif // FTPCLIENT_H
