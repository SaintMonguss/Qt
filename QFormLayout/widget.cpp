#include "widget.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QDateEdit>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLineEdit * ipAddressLineEdit = new QLineEdit(this);
    ipAddressLineEdit -> setPlaceholderText("IP aderss" );
    ipAddressLineEdit -> setInputMask("000.000.000.000;_");

    QLinedEdit* macAddressLineEdit = new QlineEdit(this);
    macAddressLineEdit -> setInputMask("HH:HH:HH:HH:HH:HH;_ ");


}

Widget::~Widget()
{
}

