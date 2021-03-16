#ifndef PIPCOLLECTION_H
#define PIPCOLLECTION_H

#include <QObject>

class PIPCollection : public QObject
{
    Q_OBJECT
public:
    explicit PIPCollection(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PIPCOLLECTION_H