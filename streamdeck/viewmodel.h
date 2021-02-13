#ifndef VIEWMODEL_H
#define VIEWMODEL_H
#include "messenger.h"

#include <QObject>

class viewmodel : public QObject
{
    Q_OBJECT
    Messaging::Messenger m_messenger;
    int m_state; //0: [STA=0,STO=0], 1: [STA=1,STA=0], 2: [STA=1,STO=1]
public:
    explicit viewmodel(QObject *parent = nullptr);
    Q_INVOKABLE bool run(const int &argAction);
signals:

public slots:
};

#endif // VIEWMODEL_H
