#ifndef UIPROPERTIES_H
#define UIPROPERTIES_H

#include <QObject>
#include <uitextproperties.h>

class UIProperties : public QObject
{
    Q_OBJECT
    qreal m_height, m_width, m_dpi;
    UITextProperties m_text;
private:
    qreal height() const
    {
        return m_height;
    }
    qreal width() const
    {
        return m_width;
    }
    qreal dpi() const
    {
        return m_dpi;
    }
    void setHeight(const qreal& argHeight)
    {
        if(m_height != argHeight)
        {
            m_height = argHeight;
            emit heightChanged();
        }
    }
    void setWidth(const qreal& argWidth)
    {
        if(m_width != argWidth)
        {
            m_width = argWidth;
            emit widthChanged();
        }
    }
    void setDpi(const qreal &argDpi)
    {
        if(m_dpi != argDpi)
        {
            m_dpi = argDpi;
            emit dpiChanged();
        }
    }
    UITextProperties* text()
    {
        return &m_text;
    }
public:
    explicit UIProperties(QObject *parent = nullptr);
    Q_PROPERTY(qreal height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(qreal width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(qreal dpi READ dpi WRITE setDpi NOTIFY dpiChanged)
    Q_PROPERTY(UITextProperties* text READ text CONSTANT)

signals:
    void heightChanged();
    void widthChanged();
    void dpiChanged();
};

#endif // UIPROPERTIES_H
