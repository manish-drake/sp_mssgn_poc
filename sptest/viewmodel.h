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
    QString m_header, m_body, m_footer;
public:
    explicit viewmodel(QObject *parent = nullptr);
    ~viewmodel();
    Q_INVOKABLE void send();
    Q_INVOKABLE void ftp();
    Q_INVOKABLE void start();
    Q_PROPERTY(QString header READ header WRITE setHeader NOTIFY headerChanged)
    Q_PROPERTY(QString body READ body WRITE setBody NOTIFY bodyChanged)
    Q_PROPERTY(QString footer READ footer WRITE setFooter NOTIFY footerChanged)

    QString header()
    {
        return m_header;
    }
    QString body()
    {
        return m_body;
    }
    QString footer()
    {
        return m_footer;
    }
    void setHeader(const QString & val)
    {
        m_header = val;
        emit headerChanged();
    }
    void setBody(const QString & val)
    {
        m_body = val;
        emit bodyChanged();
    }
    void setFooter(const QString & val)
    {
        m_footer = val;
        emit footerChanged();
    }
signals:
    void headerChanged();
    void bodyChanged();
    void footerChanged();
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
