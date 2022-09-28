#ifndef BALL_H
#define BALL_H

#include <QWidget>

class Ball : public QWidget
{
public:
    explicit Ball(QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent *e);

signals:

};

#endif // BALL_H
