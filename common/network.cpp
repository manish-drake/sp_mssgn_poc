#include "network.h"
#include <QHostAddress>
#include <QNetworkInterface>
#include "logger.h"

network::network(QObject *parent) : QObject(parent)
{
    QStringList names;
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    for(int nIter=0; nIter<list.count(); nIter++)
        names << list[nIter].humanReadableName();

    m_interfaces.setStringList(names);
    emit interfacesChanged();
}

void network::interfaceChanged(QString intr)
{
    LOGINFOZ("Interface changed: %s", intr.toStdString().c_str());
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    for(int nIter=0; nIter<list.count(); nIter++)
        if(list[nIter].humanReadableName() == intr)
        {
            const QList<QNetworkAddressEntry> &networkAddressEntries = list[nIter].addressEntries();
            for(auto &networkAddress: networkAddressEntries)
            {
                if(!networkAddress.ip().isLoopback())
                    if (networkAddress.ip().protocol() == QAbstractSocket::IPv4Protocol )
                    {
                        LOGINFOZ("Local IP selected: %s", networkAddress.ip().toString().toStdString().c_str());
                        setSelectedIP(networkAddress.ip().toString());
                        emit ipSelected(networkAddress.ip().toString());
                    }
            }
        }
}
