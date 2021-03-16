#ifndef VIEWMODEL_H
#define VIEWMODEL_H
#include "messenger.h"
#include "delegate.h"
#include "listener.h"
#include "idelegator.h"
#include <QObject>
#include "../common/multilistener.h"

#define PORT 8283
class viewmodel : public QObject, IDelegator
{
    Q_OBJECT
    void OnAcknowledgement(const char* from, const char* args) override;
    void OnException(const char* from, const char* args) override;
    void OnUnknownMessage(const char* from, const char* args) override;
    void OnSourceIdle(const char* from, const char* args) override;
    void OnReplySources(const char* from, const char* args) override;


    Messaging::Messenger m_messenger;
    int m_state; //0: [STA=0,STO=0], 1: [STA=1,STA=0], 2: [STA=1,STO=1]
    Messaging::Listener m_listener;
    Messaging::Delegate m_broker;
    MultiListener m_multListener;

    std::string m_epSrv;
    std::vector<std::string> m_epSrcs;
private:
    int state() const
    {
        return  m_state;
    }
    void setState(int st)
    {
        if(st != m_state)
        {
            m_state = st;
            emit stateChanged();
        }
    }
    QString m_ident, m_status;
    QString ident() const
    {
        return m_ident;
    }
    QString status() const
    {
        return m_status;
    }
    void setIdent(QString id)
    {
        if(m_ident != id)
        {
            m_ident = id;
            emit identChanged();
        }
    }
    void setStatus(QString sts)
    {
        if(m_status != sts)
        {
            m_status = sts;
            emit statusChanged();
        }
    }
public:
    explicit viewmodel(QObject *parent = nullptr);
    Q_INVOKABLE bool run(const int &argAction);
    Q_INVOKABLE void start();
    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString ident READ ident WRITE setIdent NOTIFY identChanged)
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged)

signals:
    void stateChanged();
    void sourecesChanged();
    void identChanged();
    void statusChanged();

public slots:
    void ipSelected(QString ip);
};

#endif // VIEWMODEL_H
