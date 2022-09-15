#include "widget.h"

#include <QLineEdit>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLineEdit *lineEdit = new QLineEdit();
    lineEdit -> setInputMask("099.000.999");
    lineEdit ->setPlaceholderText("input the number");
    lineEdit -> show();

    return a.exec();
}
