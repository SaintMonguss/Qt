#include "webbrower.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WebBrower w;
    w.show();
    return a.exec();
}
