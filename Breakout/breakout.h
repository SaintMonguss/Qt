#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QWidget>
#include <QMouseEvent>
#include <QkeyEvent>

class QLabel;

class Breakout : public QWidget
{
    Q_OBJECT

public:
    Breakout(QWidget *parent = nullptr);
    ~Breakout();

protected:
    void keyPressEvent(QKeyEvent *);
    void mouseMoveEvent(QMouseEvent *e);

    static const int MOVE_SPEED = 5;

private:
    static const int NO_OF_BRICKS = 30;

    QLabel *ball;
    QLabel *paddle;
    QLabel *bricks[NO_OF_BRICKS];
};
#endif // BREAKOUT_H
