#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientmanager2.h"
#include "productmanager2.h"
#include "ordermanager2.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ClientManager *clientManager;
    ProductManager *productManager;
    OrderManager *orderManager;
};
#endif // MAINWINDOW_H
