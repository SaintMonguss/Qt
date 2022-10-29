#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "clientmanagerform.h"
#include "productmanagerform.h"
#include "ordermanagerform.h"
#include "chatserverform.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chatServerForm = new ChatServerForm(this);
    chatServerForm->setWindowTitle(tr("Chatting Server"));

    orderForm = new OrderManagerForm(this);
    orderForm->setWindowTitle(tr("Order Info"));
    connect(orderForm, SIGNAL(destroyed()),
            orderForm, SLOT(deleteLater()));

    clientForm = new ClientManagerForm(this);
    connect(clientForm, SIGNAL(destroyed()),
            clientForm, SLOT(deleteLater()));
    connect(clientForm, SIGNAL(clientAdded(int, QString)),
            orderForm, SLOT(addClient(int, QString)));
    connect(clientForm, SIGNAL(sendClientInfo(QString, QString, QString)),
            orderForm, SLOT(getClientInfo(QString, QString, QString)));
    connect(clientForm, SIGNAL(clientAdded(int, QString)),
            chatServerForm, SLOT(addClient(int, QString)));

    clientForm->loadData();
    clientForm->setWindowTitle(tr("Client Info"));

    productForm = new ProductManagerForm(this);
    connect(productForm, SIGNAL(destroyed()),
            productForm, SLOT(deleteLater()));
    connect(productForm, SIGNAL(productAdded(int, QString)),
            orderForm, SLOT(addProduct(int, QString)));
    connect(productForm, SIGNAL(sendProductInfo(QString, int, int)),
            orderForm, SLOT(getProductInfo(QString, int, int)));

    productForm->loadData();
    productForm->setWindowTitle(tr("Product Info"));

    orderForm->loadData();
    connect(orderForm, SIGNAL(getClientInfo(int)),
            clientForm, SLOT(acceptClientInfo(int)));
    connect(orderForm, SIGNAL(getProductInfo(int)),
            productForm, SLOT(acceptProductInfo(int)));

    QMdiSubWindow *cw = ui->mdiArea->addSubWindow(clientForm);
    ui->mdiArea->addSubWindow(productForm);
    ui->mdiArea->addSubWindow(orderForm);
    ui->mdiArea->addSubWindow(chatServerForm);
    ui->mdiArea->setActiveSubWindow(cw);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionClient_triggered()
{
    if(clientForm != nullptr) {
        clientForm->setFocus();
    }
}

void MainWindow::on_actionProduct_triggered()
{
    if(productForm != nullptr) {
        productForm->setFocus();
    }
}

void MainWindow::on_actionOrder_triggered()
{
    if(orderForm != nullptr) {
        orderForm->setFocus();
    }
}


void MainWindow::on_actionChatting_triggered()
{
    if(chatServerForm != nullptr) {
        chatServerForm->setFocus();
    }
}

