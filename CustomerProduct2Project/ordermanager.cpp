#include "ordermanager.h"
#include "ui_ordermanager.h"

#include <iostream>
#include <QString>
#include <iomanip>
#include <QMessageBox>
#include <QMenu>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlTableModel>

// 생성자 파일 불러오기
OrderManager::OrderManager(QWidget *parent) : QWidget(parent),
    ui(new Ui::OrderManager)
{
    ui->setupUi(this);

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(DelObj()));

    menu = new QMenu;
    menu -> addAction(removeAction);
    ui -> orderTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
    //커스텀 슬롯 구현
    connect(ui -> orderTreeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui -> orderSearchButton, SIGNAL(clicked()), SLOT(SearchObj()));
    connect(ui -> orderModifyButton, SIGNAL(clicked()), this, SLOT(ModiObj()));
    connect(ui -> orderInputConfirmButton, SIGNAL(clicked()), SLOT(AddObj()));
    connect(ui -> orderResetButton, SIGNAL(clicked()), SLOT(resetSearchResult()));
}
    //DB 관련 선언부
void OrderManager::loadData()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE","orderDBConnection");
    db.setDatabaseName("orderlist.db");
    if (db.open( )) {
        QSqlQuery query(db);
        query.exec("CREATE TABLE IF NOT EXISTS orderInfo"
                   "(id INTEGER Primary Key AUTOINCREMENT,"
                   "clientId INTEGER NOT NULL,"
                   "clientName VARCHAR(20),"
                   "productId INTEGER NOT NULL,"
                   "productName VARCHAR(40),"
                   "date VARCHAR(30) NOT NULL,"
                   "orderPrice INTEGER,"
                   "orderStock INTEGER NOT NULL,"
                   "isdelete BOOLEAN NOT NULL CHECK (isdelete IN (0, 1)));");
        orderModel = new QSqlTableModel(nullptr, db);
        orderModel->setTable("orderInfo");
        orderModel->setFilter("isdelete = 0");
        orderModel->select();
        orderModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        orderModel->setHeaderData(1, Qt::Horizontal, tr("clientId"));
        orderModel->setHeaderData(2, Qt::Horizontal, tr("clientName"));
        orderModel->setHeaderData(3, Qt::Horizontal, tr("productId"));
        orderModel->setHeaderData(4, Qt::Horizontal, tr("productName"));
        orderModel->setHeaderData(5, Qt::Horizontal, tr("date"));
        orderModel->setHeaderData(6, Qt::Horizontal, tr("orderPrice"));
        orderModel->setHeaderData(7, Qt::Horizontal, tr("orderStock"));

        ui-> orderTreeView -> setModel(orderModel);
        ui-> orderTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
        ui -> orderTreeView->setColumnHidden(8, true);
    }
}

//소멸자 파일 저장
OrderManager::~OrderManager()
{
    delete ui;
    QSqlDatabase db = orderModel->database();
    if(db.isOpen())
    {
        orderModel->submitAll();
        db.close();
    }
}

void OrderManager::AddObj()
{
    QString clientName, productName, date;
    int orderId, clientId, productId, orderStock;

    if(ui -> orderInputIdText->text() != "")
    {
        QMessageBox::information(this, "ID 입력 금지", "신규 주문내역 등록시에는 ID 입력 금지");
        return;
    }
    if(
            ui -> orderInputClientIdText->text() != "" &&
            ui -> orderInputProductIdText->text() != "" &&
            ui -> orderInputDateText->text() != "" &&
            ui -> orderInputOrderStockText->text() != "")
    {
        clientId = ui -> orderInputClientIdText->text().toInt();
        productId = ui -> orderInputProductIdText -> text().toInt();
        date = ui -> orderInputDateText->text();
        orderStock = ui -> orderInputOrderStockText -> text().toInt();
        QSqlDatabase db = QSqlDatabase::database("orderDBConnection");
        QSqlQuery query(db);
        query.prepare("INSERT INTO orderInfo VALUES (?, ?, ?, ?, ?, ?, ?, 0)");
        query.bindValue(1, clientId);
        query.bindValue(3, productId);
        query.bindValue(5, date);
        query.bindValue(6, orderStock);
        query.exec();
        orderId = (orderModel->rowCount());

        emit requestClientInfo(orderId, clientId);
        emit requestProductInfo(orderId, productId);

        orderModel->setFilter("isdelete = 0");
        orderModel->select();
        ui->orderTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

        ui -> orderInputIdText -> clear();
        ui -> orderInputClientIdText-> clear();
        ui -> orderInputClientNameText -> clear();
        ui -> orderInputProductIdText-> clear();
        ui -> orderInputDateText -> clear();
        ui -> orderInputOrderPriceText -> clear();
        ui -> orderInputOrderStockText -> clear();
        return ;

    }

    QMessageBox::information(this, "미기입 정보", "구매자 ID, 상품ID, 구매일, 수량은 반드시 기입해주세요");
    return;
}

// 주문 정보 삭제
void OrderManager::DelObj()
{
    QModelIndex index = ui->orderTreeView->currentIndex();
    if(index.isValid())
    {
        orderModel->setData(index.siblingAtColumn(8), 1);
        orderModel->submit();
        orderModel->select();
        ui->orderTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
}

// 주문 이력 수정
void OrderManager::ModiObj()
{
    if(
            ui -> orderInputIdText -> text() != "" &&
            ui -> orderInputClientIdText -> text() != "" &&
            ui -> orderInputClientNameText -> text() != "" &&
            ui -> orderInputProductIdText -> text() != "" &&
            ui -> orderInputDateText -> text() != "" &&
            ui -> orderInputOrderPriceText -> text() != "" &&
            ui -> orderInputOrderStockText -> text() != "")
    {
        QModelIndex index = ui-> orderTreeView -> currentIndex();
        if(index.isValid())
        {
            QString clientName, date;
            int orderPrice, orderStock;
            clientName = ui-> orderInputClientNameText ->text();
            date = ui-> orderInputDateText ->text();
            orderPrice = ui -> orderInputOrderPriceText -> text().toInt();
            orderStock = ui -> orderInputOrderStockText -> text().toInt();

            orderModel->setData(index.siblingAtColumn(2), clientName);
            orderModel->setData(index.siblingAtColumn(5), date);
            orderModel->setData(index.siblingAtColumn(6), orderPrice);
            orderModel->setData(index.siblingAtColumn(7), orderStock);
            orderModel->submit();
            orderModel->select();

            ui -> orderTreeView -> header()->setSectionResizeMode(QHeaderView::ResizeToContents);
        }
        else
            QMessageBox::information(this, "안내", "수정 하고자 하는 주문의 정보를 입력해 주세요.\n "
                                                 "주문번호, 회원번호, 상품번호는 수정이 불가합니다.");
        return;
    }
}

// 주문 정보 검색
void OrderManager::SearchObj()
{
    QString target = ui-> orderComboBox->currentText();
    QString search = ui-> orderSearchText->text();
    if (target == tr("orderID"))
    {
        orderModel -> setFilter(QString("isdelete = 0 and id like '%%1%'").arg(search.toInt()));
        orderModel -> select();
        ui->orderTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    if (target == tr("clientID"))
    {
        orderModel -> setFilter(QString("isdelete = 0 and clientId like '%%1%'").arg(search.toInt()));
        orderModel -> select();
        ui->orderTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    if (target == tr("clientName"))
    {
        orderModel -> setFilter(QString("isdelete = 0 and clientName like '%%1%'").arg(search));
        orderModel -> select();
        ui->orderTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    if (target == tr("productId"))
    {
        orderModel -> setFilter(QString("isdelete = 0 and productId like '%%1%'").arg(search.toInt()));
        orderModel -> select();
        ui->orderTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    if (target == tr("productName"))
    {
        orderModel -> setFilter(QString("isdelete = 0 and productName like '%%1%'").arg(search));
        orderModel -> select();
        ui->orderTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    if (target == tr("date"))
    {
        orderModel -> setFilter(QString("isdelete = 0 and date like '%%1%'").arg(search));
        orderModel -> select();
        ui->orderTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    if (target == tr("orderPrice"))
    {
        orderModel -> setFilter(QString("isdelete = 0 and orderPrice like '%%1%'").arg(search.toInt()));
        orderModel -> select();
        ui->orderTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    return;
    if (target == tr("orderStock"))
    {
        orderModel -> setFilter(QString("isdelete = 0 and orderStock like '%%1%'").arg(search.toInt()));
        orderModel -> select();
        ui->orderTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    return;
}

//선택시 메뉴 열리기
void OrderManager::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui-> orderTreeView -> mapToGlobal(pos);
    menu -> exec(globalPos);
}

//선택한 항목 속성 값 라인에디터에 표시
void OrderManager::on_orderTreeView_clicked(const QModelIndex &index)
{
    QString orderId = orderModel->data(index.siblingAtColumn(0)).toString();
    QString clientId = orderModel->data(index.siblingAtColumn(1)).toString();
    QString clientName = orderModel->data(index.siblingAtColumn(2)).toString();
    QString productId = orderModel->data(index.siblingAtColumn(3)).toString();
    QString date = orderModel->data(index.siblingAtColumn(5)).toString();
    QString orderPrice = orderModel->data(index.siblingAtColumn(6)).toString();
    QString orderStock = orderModel->data(index.siblingAtColumn(7)).toString();

    ui -> orderInputIdText -> setText(orderId);
    ui -> orderInputClientIdText -> setText(clientId);
    ui -> orderInputClientNameText -> setText(clientName);
    ui -> orderInputProductIdText -> setText(productId);
    ui -> orderInputDateText -> setText(date);
    ui -> orderInputOrderPriceText -> setText(orderPrice);
    ui -> orderInputOrderStockText -> setText(orderStock);
}


void OrderManager::resetSearchResult()
{
    ui -> orderSearchText-> clear();
    orderModel->setFilter("isdelete = 0");
    orderModel->select();
    ui->orderTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}



void OrderManager::receiveClientInfo(int id, QString name, QString ph, QString address, QString email)
{
    QSqlQuery query(orderModel->database());
    query.prepare(QString("UPDATE order SET clientName = %1 where id = %2)").arg(name, id));
    query.exec();
}

void OrderManager::receiveProductInfo(int id, QString name, QString brand, int price, int stock)
{
    QSqlQuery query(orderModel->database());
    query.prepare(QString("UPDATE order SET productName = %1 where id = %2)").arg(name, id));
    query.prepare(QString("UPDATE order SET productPrice = %1 where id = %2)").arg(price, id));
    query.exec();
}
