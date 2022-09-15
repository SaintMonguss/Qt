#include "widget.h"
#include <QSplitter>
#include <QLabel>
#include <QDial>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLabel* label = new QLabel("&aIP Address", this);
    QDial* dial = new QDial(this);

    QSplitter *splitter = new QSplitter(this);
    splitter -> addWidget(label);
    splitter ->addWidget(dial);

    label -> setBuddy(dial);
    QDial *dial2 = new QDial(this);
    splitter -> addWidget(dial2);
    resize(splitter ->sizeHint());
}

Widget::~Widget()
{
}

