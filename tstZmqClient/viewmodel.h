#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>

class ViewModel : public QObject
{
    Q_OBJECT
public:
    explicit ViewModel(QObject *parent = nullptr);
    Q_INVOKABLE void send();

signals:

public slots:
};

#endif // VIEWMODEL_H
