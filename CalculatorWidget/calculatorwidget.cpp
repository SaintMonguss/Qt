#include "calculatorwidget.h"

#include <QPushButton>
#include <QLabel>
#include <qvector.h>

#define WIDTH 4

CalculatorWidget::CalculatorWidget(QWidget *parent)
    : QMainWindow(parent)
{
    char calculate_button [16][2] =
    {
        "7" , "8" , "9" , "/",
        "4" , "5" , "6" , "*",
        "1" , "2" , "3" , "-",
        "0" , "C" , "=" , "+"
    };

    answer = new QLabel("0", this);
    answer ->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    answer -> setGeometry(10, 5, 230, 40);

    QPushButton* buttons[16];
    for(int y = 0 ; y < WIDTH; y++)
        for(int x = 0; x < WIDTH; x++)
        {
            buttons[x+y*WIDTH] = new QPushButton(calculate_button[x+y*WIDTH], this);
            buttons[x+y*WIDTH] ->setGeometry(5+60*x, 55+60*y, 60, 60);
        }
    connect(buttons[0], SIGNAL(clicked()), SLOT(num7()));\
    connect(buttons[1], &QPushButton::clicked, [=](){answer->text() 0 ? });

}

void CalculatorWidget::num7()
{
    QString str = answer->text();
    if(str == "0")
    {
        answer->setText("7");
    }
    else
    {
        answer->setText(str+"7");
    }

}

CalculatorWidget::~CalculatorWidget()
{
}

void CalculatorWidget::numButton()
{
    QPushButton* button = (QPushButton*)sender();
    QString bStr = button->text();
    QLabel* label = findChild<QLabel*>("label1");
    QString lStr = label->text();
    label->setText(label->text()=="0"?lStr:lStr+bStr);
}
