#include "widget.h"

#include <QApplication>
#include <QPushButton>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setObjectName("parent");
    QPushButton *quit = new QPushButton("Quit", &w);
    quit -> setGeometry(75,30,62,40);
    QObject::connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    w.setGeometry(86,70,200,120);
    w.show();
    w.dumpObjectTree();
    return a.exec();
}
