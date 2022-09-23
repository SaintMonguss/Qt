#include "widget.h"
#include <QTime>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QLabel(parent)
{
//    setText("Timer");

//    int id1 = startTimer(500);
//    int id2 = startTimer(4000);
    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), SLOT(displayClock()));
    displayClock();
    timer ->start(1000);
    resize(04, 50);

}

Widget::~Widget()
{

}

void Widget::displayClock()
{
    setText(QTime::currentTime().toString());
}

