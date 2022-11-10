#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSize>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    chatServerForm = new ChatServerForm;
    clientManager = new ClientManager;
    productManager = new ProductManager;
    orderManager = new OrderManager(clientManager,productManager);


    ui -> tabWidget->setIconSize(QSize(50,50));
    ui -> tabWidget->insertTab(0, clientManager, QIcon(":/images/customer.png"), tr(""));
    ui -> tabWidget->insertTab(1, productManager, QIcon(":/images/product.png"), tr(""));
    ui -> tabWidget->insertTab(2, orderManager, QIcon(":/images/order2.png"), tr(""));
    ui -> tabWidget -> insertTab(4, chatServerForm, QIcon(":/images/chat.png"), tr(""));


    connect(clientManager, SIGNAL(clientAdded(int, QString)),
            chatServerForm, SLOT(addClient(int, QString)));
    clientManager -> loadData();

}

MainWindow::~MainWindow()
{
    delete ui;
}

