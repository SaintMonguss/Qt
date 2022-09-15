#include "widget.h"
#include <QLineEdit>
#include <QGroupBox>
#include <QFormLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLineEdit* lineEdit[3];
    for(int i = 0; i < 3 ; i++) lineEdit[i] = new QLineEdit(this);

    QFormLayout *formLayout = new QFormLayout;
    formLayout -> addRow("&IP Address", lineEdit[0]);
    formLayout -> addRow("&Mac Address", lineEdit[1]);
    formLayout -> addRow("&Date", lineEdit[2]);

    QGroupBox *groupBox = new QGroupBox("&Widget Group", this);
    groupBox -> move(5,5);
    groupBox -> setLayout(formLayout);

    resize(groupBox -> sizeHint().width() + 10, groupBox-> sizeHint().height()+10);
}

Widget::~Widget()
{
}

