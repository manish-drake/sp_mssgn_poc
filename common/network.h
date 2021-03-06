#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QStringListModel>

class network : public QObject
{
    Q_OBJECT
    QStringListModel m_interfaces;
    QStringListModel* interfaces()
    {
        return &m_interfaces;
    }
    QString m_selectedIP;
    QString selectedIP() const
    {
        return m_selectedIP;
    }
    void setSelectedIP(QString ip)
    {
        m_selectedIP = ip;
        emit selectedIPChanged();
    }
public:
    explicit network(QObject *parent = nullptr);
    Q_PROPERTY(QStringListModel* interfaces READ interfaces NOTIFY interfacesChanged)
    Q_INVOKABLE void interfaceChanged(QString intr);
    Q_PROPERTY(QString selectedIP READ selectedIP WRITE setSelectedIP NOTIFY selectedIPChanged)

signals:
    void interfacesChanged();
    void ipSelected(QString ip);
    void selectedIPChanged();

public slots:
};

#endif // NETWORK_H
