#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSize>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clientManager = new ClientManager;
    productManager = new ProductManager;
    orderManager = new OrderManager(clientManager,productManager);

    ui -> tabWidget->setIconSize(QSize(50,50));
    ui -> tabWidget->insertTab(0, clientManager, QIcon(":/images/eraser.png"), tr("clientManage"));
    ui -> tabWidget->insertTab(1, productManager, tr("productManage"));
    ui -> tabWidget->insertTab(2, orderManager, tr("orderManage"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

