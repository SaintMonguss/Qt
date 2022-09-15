#include "widget.h"

#include <QStackedLayout>
#include <QHBoxLayout>
#include <QDial>
#include <QLabel>
#include <QCalendarWidget>
#include <QTextEdit>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QDial *dial = new QDial(this);
    dial -> setRange(0, 2);
    QLabel* label = new QLabel("stack%1", this);
    QCalendarWidget * calendarWidget = new QCalendarWidget(this);
    QTextEdit * textEdit = new QTextEdit("Stack3,this");

    QStackedLayout * stackedLayout = new QStackedLayout();
    stackedLayout -> addWidget(label);
    stackedLayout -> addWidget(calendarWidget);
    stackedLayout -> addWidget(textEdit);

    connect(dial, SIGNAL(valueChanged(int)))

    hBoxLayout -> addwidget(dial);

}

Widget::~Widget()
{
}

