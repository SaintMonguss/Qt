#include "widget.h"

#include <QApplication>
#include <QSpinBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSpinBox *spinBox = new QSpinBox();
    spinBox -> setRange(0,10);
    spinBox -> setSuffix("%");
    spinBox -> setWrapping(true);
    spinBox -> setSpecialValueText("안다미로");
    spinBox -> show();

    return a.exec();
}
