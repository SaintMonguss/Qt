#include "breakout.h"

#include <QLabel>
#include <QApplication>
#include <QAudioOutput>
#include <QtMultimedia/QtMultimedia>



#define WIDTH 50
#define HEIGHT 12
#define SCR_WIDTH 300
#define SCR_HEIGHT 400

Breakout::Breakout(QWidget *parent)
    : QWidget(parent),xDir(1),yDir(-1)
{

    ball = new Ball(this);
    ball -> setGeometry(SCR_WIDTH*0.8, SCR_HEIGHT*0.875, 20, 20);
    //ball -> setStyleSheet("QLabel {background-color :red; border-radius: 5px;}");
    paddle = new Paddle(this);
    paddle -> setGeometry(SCR_WIDTH*0.7, SCR_HEIGHT*0.9, WIDTH, HEIGHT);
    //paddle -> setStyleSheet("QLabel { background-color:blue;}");
    //점수 관련 표시
    score = 0;
    scoreLabel = new QLabel(this);
    scoreLabel -> setGeometry(SCR_WIDTH*0.9, SCR_HEIGHT*0.95, 30, 10);
    scoreLabel -> setText(QString::number(score));

    for (int y = 0, i =0; y< 5; y++)
    {
        for(int x = 0; x < 6 ; x++, i++)
        {
        bricks[i] = new Brick(this);
        bricks[i] -> setStyleSheet("QLabel { background-color:cyan;" "border:1px solid black}");
        bricks[i] -> setGeometry(x*WIDTH, y*HEIGHT + 30, WIDTH, HEIGHT);
        }
    }
    resize(SCR_WIDTH,SCR_HEIGHT);

    setMouseTracking(true);
    timerId = startTimer(10);

    //사운드 출력
    bgPlayer = new QMediaPlayer(this);
    bgPlayer -> setSource(QUrl::fromLocalFile(QFileInfo("background.wav").absoluteFilePath()));
    bgPlayer -> setLoops(QMediaPlayer::Infinite);
    QAudioOutput *bgOutput = new QAudioOutput;
    bgOutput -> setVolume(100);
    bgPlayer -> setAudioOutput(bgOutput);
    bgPlayer -> play();

    //이펙트 출력 정의
    effectPlayer = new QMediaPlayer(this);
    effectPlayer -> setSource(QUrl::fromLocalFile(QFileInfo("effect.wav").absoluteFilePath()));
    QAudioOutput *effectOutput = new QAudioOutput;
    effectOutput -> setVolume(50);
    effectPlayer -> setAudioOutput(effectOutput);
}

Breakout::~Breakout()
{
    delete ball;
    delete paddle;

    for (int i = 0; i < NO_OF_BRICKS; i++)
        delete bricks[i];
}


void Breakout::checkCollision()
{
    if(ball -> geometry().bottom() > height())
    {
        killTimer(timerId);
        qDebug("Game Lost");
    }

    int j = 0;
    for (int i = 0 ; i < NO_OF_BRICKS; i++)
        if (bricks[i] -> isHidden())
            j++;

    if(j == NO_OF_BRICKS)
    {
        killTimer(timerId);
        qDebug("Victory");
    }

   //사용자 패들과 충돌 처리
    if((ball -> geometry()).intersects(paddle->geometry()))
    {
        int paddleLPos = paddle -> geometry().left();
        int ballLpos = ball -> geometry().left();
        int first = paddleLPos + 8;
        int second = paddleLPos +16;
        int third = paddleLPos +24;
        int fourth = paddleLPos +32;


        if(ballLpos < first)
        {
            xDir = -1;
            yDir = -1;
        }
        if(ballLpos >= first && ballLpos < second)
        {
            xDir = -1;
            yDir *= -1;
        }
        if(ballLpos >= second && ballLpos < third)
        {
            xDir = 0;
            yDir = -1;
        }
        if(ballLpos >= third && ballLpos < fourth)
        {
            xDir = 1;
            yDir *= -1;
        }
        if(ballLpos > fourth)
        {
            xDir = 1;
            yDir = -1;
        }
        effectPlayer -> stop();
        effectPlayer -> play();

    }

    //블록의 충돌 처리
    for(int i = 0; i < NO_OF_BRICKS; i++)
    {
        if((ball->geometry()).intersects(bricks[i]->geometry()))
        {
            int ballLeft = ball ->geometry().left();
            int ballHeight = ball ->geometry().height();
            int ballWidth = ball ->geometry().width();
            int ballTop = ball ->geometry().top();
            //현재 블록의 위치를 계산
            QPoint pointRight(ballLeft + ballWidth + 1 , ballTop);
            QPoint pointLeft(ballLeft - 1 , ballTop);
            QPoint pointTop(ballLeft, ballTop -1);
            QPoint pointBottom(ballLeft, ballTop + ballHeight +1);
            if(!bricks[i] -> isHidden())
            {
                if(bricks[i] -> geometry().contains(pointRight))
                    xDir = -1;
                else if(bricks[i] -> geometry(). contains(pointLeft))
                    xDir = -1;
                if(bricks[i] -> geometry().contains(pointTop))
                    yDir = 1;
                else if(bricks[i] -> geometry(). contains(pointBottom))
                    yDir = -1;
                bricks[i] -> setHidden(true);
                score += 10;
                scoreLabel -> setText(QString::number(score));
                effectPlayer -> stop();
                effectPlayer -> play();
            }
        }
    }

}

void Breakout::keyPressEvent(QKeyEvent *e)
{
    int x;
    switch(e -> key())
    {
    case Qt::Key_Left:
        x = paddle -> pos().x();
        if (x>0)
            paddle -> move(paddle ->x()-MOVE_SPEED, paddle->y());
        break;
    case Qt::Key_Right:
        x = paddle -> pos().x();
        if (x+WIDTH < width())
            paddle -> move(paddle ->x()+MOVE_SPEED, paddle->y());
        break;
    case Qt::Key_Escape:
        qApp -> exit();
        break;
    default:
        QWidget::keyPressEvent(e);
    }
}

void Breakout::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    moveObjects();
    checkCollision();
}

void Breakout::moveObjects()
{
    ball -> move(ball -> x() + 2 * xDir, ball -> y() + 2* yDir);
    if((ball -> x() <= 0) || (ball -> x() + 10 >= SCR_WIDTH))
        xDir *= -1;
    if(ball-> y() <= 0)
        yDir = 1;
}

void Breakout::mouseMoveEvent(QMouseEvent *e)
{
    int x = e -> pos().x();
    x = (x<0) ?
                0 :(x+WIDTH > width())?
                    width()-WIDTH :x;
    paddle -> move(x, paddle -> y());
}
