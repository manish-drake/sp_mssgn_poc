#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>
#include "delegate.h"
#include "listener.h"


class viewmodel : public QObject
{
    Q_OBJECT
    QString m_header, m_body, m_footer;
public:
    explicit viewmodel(QObject *parent = nullptr);
    ~viewmodel();
    Q_INVOKABLE void start();
    Q_PROPERTY(QString header READ header WRITE setHeader NOTIFY headerChanged)
    Q_PROPERTY(QString body READ body WRITE setBody NOTIFY bodyChanged)
    Q_PROPERTY(QString footer READ footer WRITE setFooter NOTIFY footerChanged)

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
private:
    Messaging::Delegate m_worker;
    Listener m_listener;
    bool m_close = false;
public slots:
};

#endif // VIEWMODEL_H
