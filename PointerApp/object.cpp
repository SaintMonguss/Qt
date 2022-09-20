#include "object.h"

#include <QDebug>

Object::Object(QObject *parent)
    : QObject{parent}
{
    qInfo() << "Constructor" << this;
}
Object::~Object()
{
    qInfo()<< "Deconstructor" << this;
}

void Object::useWidget()
{
    if(widget.data())
    {
        qInfo() << "Widget = " << widget.data();
        widget.data() -> setObjectName("Mywidget");
    }
    else
    {
        qInfo() << "No Pointer!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
    }
}
