#include "qteditor.h"
#include "Filter.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtEditor w;
    w.show();
    filter *filter = new class filter(&w);
    a.installEventFilter(filter);
    return a.exec();
}

