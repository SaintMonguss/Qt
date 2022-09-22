#ifndef WIDGET_H
#define WIDGET_H

#include <QLabel>
#include <QWidget>

class Widget : public QLabel
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void moveEvent(QMoveEvent*);
    void closeEvent(QCloseEvent* event);
};
#endif // WIDGET_H
