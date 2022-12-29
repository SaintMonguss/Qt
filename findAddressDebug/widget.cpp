#include "widget.h"

#include <QApplication>
#include <QPushButton>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *quit = new QPushButton("Quit", this);
    quit -> resize(75, 35);
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

Widget::~Widget()
{
}

