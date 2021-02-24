#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>
#include "delegate.h"
#include "listener.h"
#include "idelegator.h"
#include "ftpclient.h"
#include "messenger.h"


class viewmodel : public QObject, IDelegator
{
    Q_OBJECT
    QString m_header, m_body, m_footer;
    void OnAcknowledgement(const char* from, const char* args) override;
    void OnException(const char* from, const char* args) override;
    void OnNewVideoAvailable(const char* from, const char* args) override;
    void OnSubscription(const char* from, const char* args) override;
    void OnStartRecording(const char* from, const char* args) override;
    void OnStopRecording(const char* from, const char* args) override;
    void OnVideoFTPComplete(const char* from, const char* args) override;
    void OnUnknownMessage(const char* from, const char* args) override;


    bool m_isRecording;
    bool isRecording() const
    {
        return m_isRecording;
    }
    void setIsRecording(bool isrecording)
    {
        m_isRecording = isrecording;
        emit isRecordingChanged();
    }
public:
    explicit viewmodel(QObject *parent = nullptr);
    ~viewmodel();
    Q_INVOKABLE void start();
    Q_PROPERTY(QString header READ header WRITE setHeader NOTIFY headerChanged)
    Q_PROPERTY(QString body READ body WRITE setBody NOTIFY bodyChanged)
    Q_PROPERTY(QString footer READ footer WRITE setFooter NOTIFY footerChanged)
    Q_PROPERTY(bool isRecording READ isRecording WRITE setIsRecording NOTIFY isRecordingChanged)

    QString header();
    QString body();
    QString footer();
    void setHeader(const QString & val);
    void setBody(const QString & val);
    void setFooter(const QString & val);

signals:
    void headerChanged();
    void bodyChanged();
    void footerChanged();
    void isRecordingChanged();
private:
    Messaging::Delegate m_broker;
    Messaging::Listener m_listener;
    Messaging::Messenger m_messenger;
    FTPClient m_ftp;
    bool m_close = false;
public slots:
};

#endif // VIEWMODEL_H
