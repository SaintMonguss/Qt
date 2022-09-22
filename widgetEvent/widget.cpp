#include "widget.h"
#include <QCloseEvent>


Widget::Widget(QWidget *parent)
    : QLabel(parent)
{
    setText(tr("Hello World"));
    resize(100, 30);
}

void Widget::moveEvent(QMoveEvent*)
{
    setText(QString("X : %1, Y : %2").arg(x()).arg(y()));
}

void Widget::closeEvent(QCloseEvent* event)
{
    event -> ignore();
}

Widget::~Widget()
{
}

