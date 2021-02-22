#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>

class FTPClient;

class viewmodel : public QObject
{
    Q_OBJECT
    FTPClient *client;
public:
    explicit viewmodel(QObject *parent = nullptr);
    Q_INVOKABLE void run();



signals:

public slots:
};

#endif // VIEWMODEL_H
