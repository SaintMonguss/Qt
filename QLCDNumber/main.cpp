#include "lcd.h"

#include <QApplication>
#include <QLCDNumber>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLCDNumber *lcd = new QLCDNumber();

    lcd->display(2002);
    lcd -> setDecMode();
    lcd->setSegmentStyle(QLCDNumber::Flat);
    lcd->show();

    return a.exec();
}
