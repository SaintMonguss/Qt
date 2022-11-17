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
    connect(ui -> orderSearchButton, SIGNAL(clicked()), SLOT(SerchObj()));
    connect(ui -> orderModifyButton, SIGNAL(clicked()), this, SLOT(ModiObj()));
    connect(ui -> orderInputConfirmButton, SIGNAL(clicked()), SLOT(AddObj()));
    connect(ui -> orderResetButton, SIGNAL(clicked()), SLOT(resetSearchResult()));

    //DB 관련 선언부
    QSqlDatabase db = QSqlDatabase::database();
    db.setDatabaseName("orderlist.db");
    if (db.open( )) {
        QSqlQuery query(db);
        query.exec("CREATE TABLE IF NOT EXISTS order"
                   "(id INTEGER Primary Key,"
                   "clientId INTEGER NOT NULL,"
                   "clientName VARCHAR(20),"
                   "productId INTEGER NOT NULL,"
                   "productName VARCHAR(40),"
                   "date VARCHAR(30) NOT NULL,"
                   "orderPrice INTEGER,"
                   "orderStock INTEGER NOT NULL;");
        //ID값 시퀀스 선언
        // 버그 가능성 있음
        query.exec("CREATE SEQUENCE IF NOT EXISTS seq_order_id"
                   "INCREMENT BY 1 "
                   "START WITH 1 ;");
        orderModel = new QSqlTableModel();
        orderModel->setTable("order");
        orderModel->setFilter("");
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

        QSqlQuery query(orderModel->database());
        query.prepare("INSERT INTO order VALUES (seq_product_id.nextval, ?, ?, ?, ?, ?, ?)");
        query.bindValue(1, clientId);
        query.bindValue(3, productId);
        query.bindValue(5, date);
        query.bindValue(6, orderStock);
        query.exec();
        orderId = query.boundValue(0).toInt();

        emit requestClientInfo(orderId, clientId);
        emit requestProductInfo(orderId, productId);

        orderModel->setFilter("");
        orderModel->select();
        ui->orderTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }

    ui -> orderInputIdText -> clear();
    ui -> orderInputClientIdText-> clear();
    ui -> orderInputClientNameText -> clear();
    ui -> orderInputProductIdText-> clear();
    ui -> orderInputDateText -> clear();
    ui -> orderInputOrderPriceText -> clear();
    ui -> orderInputOrderStockText -> clear();

    return;
}

// 주문 정보 삭제
void OrderManager::DelObj()
{
    QModelIndex index = ui->orderTreeView->currentIndex();
    if(index.isValid())
    {
        orderModel->setData(index.siblingAtColumn(5), 1);
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
void OrderManager::SerchObj()
{
    QString target = ui -> orderComboBox -> currentText();
    if (target == tr("orderID"))
        for (auto itr = orderList.begin(); itr != orderList.end(); itr++)
        {
            if (itr.value()-> GetOrderId() == ui-> orderSearchText -> text().toInt())
                itr.value()-> setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == tr("clientName"))
        for (auto itr = orderList.begin(); itr != orderList.end(); itr++)
        {
            if (itr.value()->GetClientName() == ui -> orderSearchText -> text())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == tr("clientID"))
        for (auto itr = orderList.begin(); itr != orderList.end(); itr++)
        {
            if (itr.value()->GetClientId() == ui -> orderSearchText -> text().toInt())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == tr("productName"))
        for (auto itr = orderList.begin(); itr != orderList.end(); itr++)
        {
            if (itr.value()->GetProductName() == ui -> orderSearchText -> text())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == tr("date"))
        for (auto itr = orderList.begin(); itr != orderList.end(); itr++)
        {
            if (itr.value()->GetDate() == ui -> orderSearchText ->text().toInt())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == tr("orderPrice"))
        for (auto itr = orderList.begin(); itr != orderList.end(); itr++)
        {
            if (itr.value()->GetOrderPrice() == ui -> orderSearchText ->text().toInt())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == tr("orderStock"))
        for (auto itr = orderList.begin(); itr != orderList.end(); itr++)
        {
            if (itr.value()->GetOrderStock() == ui -> orderSearchText ->text().toInt())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    return;
}

//선택시 메뉴 열리기
void OrderManager::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->orderTreeView->mapToGlobal(pos);
    menu -> exec(globalPos);
}

//선택한 항목 속성 값 라인에디터에 표시
void OrderManager::on_orderTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui -> orderInputIdText -> setText(item->text(0));
    ui -> orderInputProductNameText -> setText(item->text(3));
    ui -> orderInputClientIdText -> setText(item->text(1));
    ui -> orderInputDateText -> setText(item->text(4));
    ui -> orderInputOrderPriceText -> setText(item->text(5));
    ui -> orderInputOrderStockText -> setText(item->text(6));
}

void OrderManager::resetSearchResult()
{
    ui -> orderInputIdText -> clear();
    ui -> orderInputProductNameText -> clear();
    ui -> orderInputClientIdText -> clear();
    ui -> orderInputDateText -> clear();
    ui -> orderInputOrderPriceText -> clear();
    ui -> orderInputOrderStockText -> clear();

    for (auto itr = orderList.begin(); itr != orderList.end(); itr++)
    {
        itr.value()->setHidden(false);
    }
}

void OrderManager::on_orderTreeView_clicked(const QModelIndex &index)
{

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
    query.prepare(QString("UPDATE order SET productName = %1, productPrice = %2 where id = %3)").arg(name, price, id));
    query.exec();
}
