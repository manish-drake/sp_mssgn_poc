#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>
#include "delegate.h"
#include "listener.h"
#include "idelegator.h"
#include "ftpclient.h"
#include "messenger.h"
#include "../common/multilistener.h"

#define PORT 8284
class viewmodel : public QObject, IDelegator
{
    Q_OBJECT


    QString m_header, m_body, m_footer;
    void OnAcknowledgement(const char* from, const char* args) override;
    void OnException(const char* from, const char* args) override;
    void OnStartRecording(const char* from, const char* args) override;
    void OnStopRecording(const char* from, const char* args) override;
    void OnUnknownMessage(const char* from, const char* args) override;
    void OnReplySources(const char* from, const char* args) override;

    MultiListener m_multListener;

    std::string m_epSrv, m_epFTP;
    std::vector<std::string> m_epSrcs;


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
    QString m_fileName;
    void setFileName(const QString& name)
    {
        if(name != m_fileName)
        {
            m_fileName = name;
            emit fileNameChanged();
        }
    }
    QString fileName() const
    {
        return m_fileName;
    }
    QString m_appMediaFolder;
public:
    explicit viewmodel(QObject *parent = nullptr);
    ~viewmodel();
    Q_INVOKABLE void start();
    Q_PROPERTY(QString header READ header WRITE setHeader NOTIFY headerChanged)
    Q_PROPERTY(QString body READ body WRITE setBody NOTIFY bodyChanged)
    Q_PROPERTY(QString footer READ footer WRITE setFooter NOTIFY footerChanged)
    Q_PROPERTY(bool isRecording READ isRecording WRITE setIsRecording NOTIFY isRecordingChanged)
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

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
    void fileNameChanged();
private:
    Messaging::Delegate m_broker;
    Messaging::Listener m_listener;
    Messaging::Messenger m_messenger;
    bool m_close = false;
    QString getUniqueFileName();
public slots:
    void ipSelected(QString ip);
    void videoFTPComplete(const QString& vid);
};

#endif // VIEWMODEL_H
