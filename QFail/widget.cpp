#include "widget.h"
#include <QDebug>
#include <QTest>

Widget::Widget(QWidget *parent)
    : QObject(parent)
{
    age = 0;
}

Widget::~Widget()
{
}


void Widget::setAge(int value)
{
    age = value;
}

void Widget::testFail()
{
    QFAIL("NO REASON JUST FAIL!");
}

void Widget::testAge()
{
    if(!age) QFAIL("Age is not set!");
}

void Widget::testWidget()
{
    int value = 45;

    QVERIFY(age > 0 && age < 100);

    if(age > 40) QWARN("Age is over 40!");
    if(age <21) QFAIL("MUST BE AN ADULT");

    QCOMPARE(age, value);
}
