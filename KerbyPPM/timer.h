#ifndef TIMER_H
#define TIMER_H

#include <QTimer>

class Timer :public QObject
{
    Q_OBJECT
public:
    Timer();
    QTimer *mytimer;
public slots:
    void MyTimerSlot();
};

#endif // TIMER_H
