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
    orderManager = new OrderManager;


    ui -> tabWidget->setIconSize(QSize(50,50));
    ui -> tabWidget->insertTab(0, clientManager, QIcon(":/images/customer.png"), tr(""));
    ui -> tabWidget->insertTab(1, productManager, QIcon(":/images/product.png"), tr(""));
    ui -> tabWidget->insertTab(2, orderManager, QIcon(":/images/order2.png"), tr(""));
    ui -> tabWidget -> insertTab(4, chatServerForm, QIcon(":/images/chat.png"), tr(""));

    connect(clientManager, SIGNAL(clientAdded(int, QString)),
            chatServerForm, SLOT(addClient(int, QString)), Qt::QueuedConnection);
    clientManager -> loadData();

    // orderManager의 정보 요청에 대한 반응 연결
    connect(orderManager, SIGNAL(requestClientInfo(int)),
            clientManager, SLOT(acceptClientInfoRequest(int)));
    connect(clientManager, SIGNAL(tossClientInfo(QString, QString, QString, QString)),
            orderManager, SLOT(receiveClientInfo(QString, QString, QString, QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

