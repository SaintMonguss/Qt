#include "widget.h"

#include <QApplication>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QLabel *hello = new QLabel("Hello Qt!", 0 , Qt::FramelessWindowHint);
    hello->setCursor(Qt::WaitCursor);

    return app.exec();
}
