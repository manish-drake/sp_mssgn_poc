#ifndef TEST_H
#define TEST_H
#include <QObject>
#include "listener.h"
#include "delegate.h"
#include "idelegator.h"
#include "ftpclient.h"
#include "messenger.h"
#include "../common/multilistener.h"

#define PORT 8286
class viewmodel : public QObject, IDelegator
{
    Q_OBJECT
    void OnAcknowledgement(const char* from, const char* args) override;
    void OnException(const char* from, const char* args) override;
    void OnNewVideoAvailable(const char* from, const char* args) override;
    void OnUnknownMessage(const char* from, const char* args) override;
    int m_val;
    MultiListener m_multListener;

    std::string m_epSrv, m_epFTP;
    std::vector<std::string> m_epSrcs;
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
    Messaging::Messenger m_messenger;
    FTPClient m_ftp;
    QString m_appMediaFolder;
public:
    explicit viewmodel(QObject *parent = nullptr);
    Q_PROPERTY(int val READ val WRITE setval )
    Q_INVOKABLE void start();
signals:
public slots:
    void ipSelected(QString ip);
    void videoFetchComplete(const QString& vid);
};
#endif // TEST_H
