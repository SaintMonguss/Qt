#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QWidget>

class QLabel;

class Breakout : public QWidget
{
    Q_OBJECT

public:
    Breakout(QWidget *parent = nullptr);
    ~Breakout();\

private:
    static const int NO_OF_BRICKS = 30;

    QLabel *ball;
    QLabel *paddle;
    QLabel *bricks[NO_OF_BRICKS];
};
#endif // BREAKOUT_H
