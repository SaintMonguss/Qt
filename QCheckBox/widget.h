#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QButtonGroup>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QLabel *label;
    QCheckBox *checkBox[4];
    QButtonGroup *buttonGroup;

public slots:
    void selectButton(int id);
};
#endif // WIDGET_H
