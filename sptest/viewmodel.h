#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>
#include "delegate.h"
#include "ftpcontrolchannel.h"
#include "ftpdatachannel.h"
#include "listener.h"

struct Command {
    QString cmd;
    QString args;
};
class viewmodel : public QObject
{
    Q_OBJECT
public:
    explicit viewmodel(QObject *parent = nullptr);
    ~viewmodel();
    Q_INVOKABLE void send();
    Q_INVOKABLE void ftp();
    Q_INVOKABLE void start();
signals:
private:
    FtpDataChannel dataChannel;
    FtpControlChannel controlChannel;
    QList<Command> commands;
    Messaging::Delegate m_worker;
    Listener m_listener;
    bool m_close = false;
public slots:
};

#endif // VIEWMODEL_H
