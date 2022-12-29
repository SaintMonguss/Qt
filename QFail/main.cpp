#include "widget.h"

#include <QCoreApplication>
#include <QTest>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Widget widget;
    widget.setAge(20);
    QTest::qExec(&widget);


    return a.exec();
}
