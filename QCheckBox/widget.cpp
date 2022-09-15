#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
   label = new QLabel("0", this);
   label -> move(10, 10);
   resize(140, 110);
   buttonGroup = new QButtonGroup(this);
   buttonGroup -> setExclusive(false);
   connect(buttonGroup, SIGNAL(idClicked(int)), SLOT(selectButton(int)));
   for(int i = 0 ; i <4 ; i++)
   {
       QString str = QString("CheckBox%1").arg(i+1);
       checkBox[i] = new QCheckBox(str, this);
       checkBox[i] -> move(10, 30+20*i);
       buttonGroup -> addButton(checkBox[i], i);
   }
}

void Widget::selectButton(int id)
{
    QButtonGroup* buttonGroup = (QButtonGroup*)sender();
    QCheckBox* button = (QCheckBox*)buttonGroup -> button(id);
    qDebug("CheckBox%d is selected(%s)", id + 1, (button ->isChecked())? "on" : "Off");
    QString str1 = QString::number(id+1);
    label->setText(str1);

}

Widget::~Widget()
{
}
