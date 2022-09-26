#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QWidget>

class CustomButton : public QWidget
{
    Q_OBJECT

public:
    CustomButton(QWidget *parent = nullptr);
    ~CustomButton();
};
#endif // CUSTOMBUTTON_H
