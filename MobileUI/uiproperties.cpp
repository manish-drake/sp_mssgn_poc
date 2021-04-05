#include "uiproperties.h"
#include <QRect>
#include <QGuiApplication>
#include <QScreen>
#include <QDebug>

UIProperties::UIProperties(QObject *parent) : QObject(parent)
{

    QRect rect = QGuiApplication::primaryScreen()->geometry();
    qreal height = qMax(rect.width(), rect.height());
    qDebug() << height;
    qreal width = qMin(rect.width(), rect.height());
    qDebug() << width;
    qreal dpi = QGuiApplication::primaryScreen()->logicalDotsPerInch();
    qDebug() << dpi;

    setHeight(height);
    setWidth(width);
    setDpi(dpi);
}
