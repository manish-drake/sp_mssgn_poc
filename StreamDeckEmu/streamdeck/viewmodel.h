#ifndef VIEWMODEL_H
#define VIEWMODEL_H
#include "messenger.h"
#include "delegate.h"
#include "listener.h"
#include "idelegator.h"
#include <QObject>

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
    Messaging::Messenger m_messenger;
    int m_state; //0: [STA=0,STO=0], 1: [STA=1,STA=0], 2: [STA=1,STO=1]
    Messaging::Delegate m_broker;
    Messaging::Listener m_listener;
public:
    explicit viewmodel(QObject *parent = nullptr);
    Q_INVOKABLE bool run(const int &argAction);
    Q_INVOKABLE void start();
signals:

public slots:
};

#endif // VIEWMODEL_H
