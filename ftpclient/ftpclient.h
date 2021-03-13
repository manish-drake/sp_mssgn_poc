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
    bool m_isConnected;
    bool isConnected() const
    {
        return m_isConnected;
    }
public:
    explicit FTPClient(QObject *parent = nullptr);
    void Send(const QString &file, const QString &server);
    void Fetch(const std::string &fileName, const QString &server, const std::string &mediaFolder);
signals:
    void connectToServer(QString server);
    void videoFTPComplete(const QString& vid);
    void videoFetchComplete(const QString& vid);

public slots:
    void InvokeCallback();
};

#endif // FTPCLIENT_H
