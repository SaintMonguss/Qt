#include "widget.h"

#include <QApplication>
#include <QProgressBar>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QProgressBar *progBar = new QProgressBar();
    progBar -> setValue(20);
    progBar -> show();
    return a.exec();
}
