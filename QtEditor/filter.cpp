#include "filter.h"

#include <QEvent>
#include <QDebug>

filter::filter(QObject *parent) : QObject{parent}
{
}

bool filter::eventFilter(QObject *obj, QEvent *event)
{
    if(event -> type() == QEvent::MouseButtonPress)
    {
        qDebug() << "Event hijacked in filter";
        return true;
    }
    return QObject::eventFilter(obj, event);
}
