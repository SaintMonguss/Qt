#include "widget.h"

#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPushButton *pushButton = new QPushButton("Push&Button", 0);
    QObject::connect(pushButton,SIGNAL(clicked()), &a, SLOT(quit()));
    pushButton -> show();
    return a.exec();0
}
