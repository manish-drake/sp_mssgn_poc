#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>

class ViewModel : public QObject
{
    Q_OBJECT
    int m_state;
    int state() const
    {
        return m_state;
    }
    void setState(int st)
    {
        m_state = st;
    }
public:
    explicit ViewModel(QObject *parent = nullptr);
    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)
    bool blSt;
    Q_INVOKABLE void start();
signals:
    void stateChanged(int st);

public slots:
};

#endif // VIEWMODEL_H
