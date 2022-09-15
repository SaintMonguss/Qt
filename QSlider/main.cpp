#include "widget.h"

#include <QApplication>
#include <QSlider>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSlider *slider = new QSlider();
    slider -> setOrientation(Qt::Horizontal);
    slider -> setTickPosition(QSlider::TicksAbove);
    slider -> setStyle(QStyleFactory::create("Fusion"));
    slider -> setValue(33);
    slider -> show();

    return a.exec();
}
