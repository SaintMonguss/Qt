#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <QWidget>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QMediaPlayer>

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
    void timerEvent(QTimerEvent *);
    void moveObjects();
    void checkCollision();

    static const int MOVE_SPEED = 5;

private:
    static const int NO_OF_BRICKS = 30;
    int score;
    QLabel *ball;
    QLabel *paddle;
    QLabel *bricks[NO_OF_BRICKS];
    QLabel *scoreLabel;
    QMediaPlayer *bgPlayer;
    QMediaPlayer *effectPlayer;
    int timerId;
    int xDir, yDir;
};
#endif // BREAKOUT_H
