#include "widget.h"
#include <QPicture>
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPicture picture;
    QPainter painter;
    painter.begin(&picture);
    painter.drawEllipse(10,20,80,70);
    painter.end();
    picture.save("drawing.pic");

}

Widget::~Widget()
{
}


void Widget::paintEvent(QPaintEvent *)
{
    QPicture picture;
    picture.load("drawing.pic");
    QPainter painter;
    painter.begin(this);
    painter.drawPicture(0,0, picture);
    painter.end();
}
