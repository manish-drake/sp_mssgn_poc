#ifndef VIEWMODEL_H
#define VIEWMODEL_H
#include "messenger.h"
#include "delegate.h"
#include "listener.h"
#include "idelegator.h"
#include <QObject>
#include "../../common/multilistener.h"

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

public:
    explicit viewmodel(QObject *parent = nullptr);
    Q_INVOKABLE bool run(const int &argAction);
    Q_INVOKABLE void start();
    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)

signals:
    void stateChanged();
public slots:
    void ipSelected(QString ip);
};

#endif // VIEWMODEL_H
