#ifndef UITEXTPROPERTIES_H
#define UITEXTPROPERTIES_H
#include <QObject>


class UITextProperties: public QObject
{
    Q_OBJECT
private:
    qreal big() const
    {
        return 18;
    }
    qreal medium() const
    {
        return 14;
    }
    qreal small() const
    {
        return 12;
    }
public:
    explicit UITextProperties(QObject *parent = nullptr);
    Q_PROPERTY(qreal big READ big CONSTANT)
    Q_PROPERTY(qreal medium READ medium CONSTANT)
    Q_PROPERTY(qreal small READ small CONSTANT)

};

#endif // UITEXTPROPERTIES_H
