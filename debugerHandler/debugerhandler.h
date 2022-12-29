#ifndef DEBUGERHANDLER_H
#define DEBUGERHANDLER_H

#include <QMainWindow>

class debugerHandler : public QMainWindow
{
    Q_OBJECT

public:
    debugerHandler(QWidget *parent = nullptr);
    ~debugerHandler();
};
#endif // DEBUGERHANDLER_H
