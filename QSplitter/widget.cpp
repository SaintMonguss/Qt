#include "widget.h"
#include <QSplitter>
#include <QLabel>
#include <QDial>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLabel* label = new QLabel("IP Address", this);
    QDial* dial = new QDial(this);

    QSplitter *splitter = new QSplitter(this);
    splitter -> addWidget(label);
    splitter ->addWidget(dial);

    resize(splitter ->sizeHint());
}

Widget::~Widget()
{
}

