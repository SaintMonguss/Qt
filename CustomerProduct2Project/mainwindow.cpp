#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    clientManager = new ClientManager;
    productManager = new ProductManager;
    orderManager = new OrderManager;

    ui -> tabWidget->insertTab(0, clientManager, tr("clientManage"));
    ui -> tabWidget->insertTab(1, productManager, tr("productManage"));
    ui -> tabWidget->insertTab(2, orderManager, tr("orderManage"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

