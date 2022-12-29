#ifndef CAT_H
#define CAT_H

#include <QMainWindow>

class Cat : public QMainWindow
{
    Q_OBJECT

public:
    Cat(QWidget *parent = nullptr);
    ~Cat();
};
#endif // CAT_H
