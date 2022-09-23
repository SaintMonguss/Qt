#ifndef WIDGET_H
#define WIDGET_H

#include <QLabel>

class Widget : public QLabel
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

public slots:
    void displayClock();
};
#endif // WIDGET_H
