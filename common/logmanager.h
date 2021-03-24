#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QObject>
#include <QStringListModel>


class LogManager : public QObject
{
    Q_OBJECT
    QStringListModel m_interfaces;
    QStringListModel* interfaces()
    {
        return &m_interfaces;
    }
    QStringList getLogs();
    QString filterName(const QString &filename);
    QHash<QString, QString> m_logFiles;
    QString m_serverIP;
public:
    explicit LogManager(QObject *parent = nullptr);
    Q_INVOKABLE void refresh();
    Q_INVOKABLE void ftp();
    Q_INVOKABLE void clean();
    Q_PROPERTY(QStringListModel* interfaces READ interfaces NOTIFY interfacesChanged)
signals:
    void interfacesChanged();
public slots:
    void ftpServerNotified(QString serverIP);
};

#endif // LOGMANAGER_H
