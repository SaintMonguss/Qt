#include "widget.h"
#include <QApplication>
#include <QPushButton>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *button = new QPushButton(" Quit", this);

    button -> resize(120,35);
    this -> resize(120, 35);
    move(300, 300);

    connect(button, &QPushButton::clicked, []() {qApp -> quit();});
}
void Widget::slotQuit()
{
    QLabel *label = findChild<QLabel*>("label1");
    qDebug("%s", qPrintable(label->metaObject() -> className()));
    label ->setText("World");
}

Widget::~Widget()
{
}

