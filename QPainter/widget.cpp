#include "widget.h"
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    resize(200, 200);
}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent*)
{
    QLinearGradient gradient(0, 0, 100, 180);
    gradient.setColorAt(0.0, Qt::red);
    gradient.setColorAt(1.0, Qt::green);

    QPainter painter;
    painter.begin(this);
    painter.setBrush(gradient);
    painter.drawRect(20, 20, 160,160);
    painter.end();

}
