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
    QString m_fileName;
public:
    explicit FTPClient(QObject *parent = nullptr);
    void Send(const QString &file, const QString &server);
    void Receive(const std::string &fileName, const QString &server);
signals:
    void connectToServer(QString server);
    void videoFTPComplete();

public slots:
    void InvokeCallback();
};

#endif // FTPCLIENT_H
