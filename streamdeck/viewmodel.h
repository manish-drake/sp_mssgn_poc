#ifndef VIEWMODEL_H
#define VIEWMODEL_H
#include "messenger.h"
#include "delegate.h"
#include "listener.h"

#include <QObject>

class viewmodel : public QObject
{
    Q_OBJECT
    Messaging::Messenger m_messenger;
    int m_state; //0: [STA=0,STO=0], 1: [STA=1,STA=0], 2: [STA=1,STO=1]
    Messaging::Delegate m_worker;
    Listener m_listener;
public:
    explicit viewmodel(QObject *parent = nullptr);
    Q_INVOKABLE bool run(const int &argAction);
    Q_INVOKABLE void start();
signals:

public slots:
};

#endif // VIEWMODEL_H
