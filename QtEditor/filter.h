#ifndef FILTER_H
#define FILTER_H

#include <QObject>

class filter : public QObject
{
    Q_OBJECT
public:
    explicit filter(QObject *parent = nullptr);

    bool eventFilter(QObject *, QEvent *);
};

#endif // FILTER_H
