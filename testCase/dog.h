#ifndef DOG_H
#define DOG_H

#include <QObject>
#include <QDebug>

class Dog: public QObject
{
    Q_OBJECT

public:
    explicit Dog(QObject* parent = nullptr);

private slots:
    void initTestCase();
    void init();
    void cleanup();
    void cleanupTestCase();

    void bark();
    void rollover();

    void simple();
};



#endif // DOG_H
