#include "custombutton.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CustomButton w;
    w.show();
    return a.exec();
}
