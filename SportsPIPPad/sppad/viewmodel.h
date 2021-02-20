#ifndef TEST_H
#define TEST_H
#include <QObject>
#include "listener.h"
#include "delegate.h"
#include "idelegator.h"
#include "ftpclient.h"

class viewmodel : public QObject, IDelegator
{
    Q_OBJECT
    void OnAcknowledgement(const char* from, const char* args) override;
    void OnException(const char* from, const char* args) override;
    void OnNewVideoAvailable(const char* from, const char* args) override;
    void OnSubscription(const char* from, const char* args) override;
    void OnStartRecording(const char* from, const char* args) override;
    void OnStopRecording(const char* from, const char* args) override;
    void OnVideoFTPComplete(const char* from, const char* args) override;
    void OnUnknownMessage(const char* from, const char* args) override;
    int m_val;
    int val()
    {
        return m_val;
    }
    void setval(int val)
    {
        m_val=val;
    }


    Messaging::Listener m_listener;
    Messaging::Delegate m_broker;
    FTPClient m_ftp;
public:
    explicit viewmodel(QObject *parent = nullptr);
    Q_PROPERTY(int val READ val WRITE setval )
    Q_INVOKABLE void start();
signals:
public slots:
};
#endif // TEST_H
