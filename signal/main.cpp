#include <QCoreApplication>
#include "counter.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    counter b,c;
    connect(&b, SIGNAL(valueChanged(int)), &c, SLOT(setValue(int)));
    return a.exec();
}
