#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QRadioButton>
#include <QButtonGroup>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QRadioButton *radioButton[4];
    QButtonGroup *buttonGroup;
};
#endif // WIDGET_H
