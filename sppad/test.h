#ifndef TEST_H
#define TEST_H
#include <QObject>
#include "listener.h"
#include "delegate.h"
class test : public QObject
{
    Q_OBJECT
    int m_val;
    int val()
    {
        return m_val;
    }
    void setval(int val)
    {
        m_val=val;
    }


    Listener m_listener;
    Messaging::Delegate m_worker;
public:
    explicit test(QObject *parent = nullptr);
    Q_PROPERTY(int val READ val WRITE setval )
    Q_INVOKABLE void start();
signals:
public slots:
};
#endif // TEST_H
