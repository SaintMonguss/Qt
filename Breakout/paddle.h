#ifndef PADDLE_H
#define PADDLE_H

#include <QLabel>

class Paddle : public QLabel
{
    Q_OBJECT
public:
    explicit Paddle(QWidget *parent = nullptr);

signals:

};

#endif // PADDLE_H
