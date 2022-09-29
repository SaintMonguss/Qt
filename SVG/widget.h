#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSvgWidgets/QSvgWidget>

class Widget : public QWidget
{

    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    QImage buffer;

public:
    void paintEvent(QPaintEvent *);
};
#endif // WIDGET_H
