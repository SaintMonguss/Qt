#include "widget.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QValidator>
#include <QLabel>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    QDoubleValidator* doubleValidator = new QDoubleValidator(this);
    doubleValidator -> setBottom(10.0);
    doubleValidator -> setTop(100.0);
    doubleValidator -> setDecimals(3);

    QIntValidator * intValidator = new QIntValidator(this);
    intValidator -> setBottom(13);
    intValidator -> setTop(19);

    QRegularExpressionValidator *regExpValidator = new QRegularExpressionValidator(this);
    regExpValidator ->setRegularExpression
            (
                QRegularExpression
                (
                "^(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\."
                "(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$"
                )
            );
    QLineEdit * lineEditDouble = new QLineEdit(this);
    lineEditDouble -> setValidator(doubleValidator);

    QLineEdit* lineEditInt = new QLineEdit(this);
    lineEditInt -> setValidator(intValidator);

    QLineEdit* lineEditRegExp = new QLineEdit(this);
    lineEditRegExp -> setValidator(regExpValidator);

    QFormLayout *formLayout =new QFormLayout(this);
    formLayout -> addRow("&Double", lineEditDouble);
    formLayout -> addRow("&Int", lineEditInt);
    formLayout -> addRow("&Regular Expression", lineEditRegExp);

    setWindowTitle("monguss");

}

Widget::~Widget()
{
}

