#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSize>
#include <QString>


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

    //채팅 참여자 목록 추가/제거 연동에 관한 연결
    connect(clientManager, SIGNAL(clientAdded(int, QString)),
            chatServerForm, SLOT(addClient(int, QString)), Qt::QueuedConnection);
    connect(clientManager, SIGNAL(clientDeleted(int, QString)),
            chatServerForm, SLOT(deleteClient(int, QString)), Qt::QueuedConnection);
    clientManager -> loadData();

    // orderManager의 정보 요청에 대한 반응 연결
    //client측
    connect(orderManager, SIGNAL(requestClientInfo(int, int)),
            clientManager, SLOT(acceptClientInfoRequest(int, int)));
    connect(clientManager, SIGNAL(sendClientInfo(int, QString, QString, QString, QString)),
            orderManager, SLOT(receiveClientInfo(int, QString, QString, QString, QString)));
    //product측
    connect(orderManager, SIGNAL(requestProductInfo(int, int)),
            productManager, SLOT(acceptProductInfoRequest(int, int)));
    connect(productManager, SIGNAL(sendProductInfo(int, QString, QString, int, int)),
            orderManager, SLOT(receiveProductInfo(int, QString, QString, int, int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

