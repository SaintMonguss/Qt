#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>

#include "clientmanager.h"
#include "productmanager.h"
#include "ordermanager.h"
#include "chatserverform.h"

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
    ChatServerForm *chatServerForm;
};
#endif // MAINWINDOW_H
