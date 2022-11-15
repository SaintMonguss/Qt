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
                   "clientName VARCHAR(20) NOT NULL,"
                   "productId INTEGER NOT NULL,"
                   "productName VARCHAR(40) NOT NULL,"
                   "date VARCHAR(30) NOT NULL,"
                   "orderPrice INTEGER NOT NULL,"
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



//주문 정보 추가
//void OrderManager::AddObj()
//{
//    Order* order;
//    int id;

//    if(ui -> orderInputIdText->text() != "")
//    {
//        QMessageBox::information(this, "ID 입력 금지", "신규 주문 등록시에는 ID 입력 금지");
//        return;
//    }
//    if(
//            ui -> orderInputClientIdText->text() != "" &&
//            ui -> orderInputProductNameText->text() != "" &&
//            ui -> orderInputDateText->text() != "" &&
//            ui -> orderInputOrderPriceText->text() != "" &&
//            ui -> orderInputOrderStockText->text() != ""
//            )
//    {
//        // 널 포인터 체크 - 존재하지 않는 고객 ID 입력시 널 포인트가 반환될 가능성
//        if(CM -> TossObj(ui -> orderInputClientIdText->text().toInt()) == nullptr )
//        {
//            QMessageBox::information(this, "안내", "해당 하는 ID의 고객이 없습니다.");
//            return;
//        }
//        if (orderList.empty())
//        {
//            idHistory  = id = 1;
//        }
//        else
//        {
//            id = idHistory + 1;
//            idHistory += 1;
//        }
//        order = new Order(id);
//        order -> SetClientId((ui -> orderInputClientIdText->text()).toInt());
//        order -> SetProductName(ui -> orderInputProductNameText->text());
//        order -> SetOrderStock(ui -> orderInputOrderStockText -> text().toInt());
//        order -> SetDate(ui -> orderInputDateText -> text().toInt());
//        order -> SetOrderPrice(ui -> orderInputOrderPriceText -> text().toInt());
//        order -> SetClientName(CM -> TossObj(order->GetClientId()) -> GetName());

//        orderList.insert(id, order);
//        ui -> orderTreeWidget ->addTopLevelItem(order);
//        ui -> orderTreeWidget -> update();
//        return;
//    }
//    ui -> orderInputClientIdText-> clear();
//    ui -> orderInputProductNameText -> clear();
//    ui -> orderInputOrderStockText -> clear();
//    ui -> orderInputOrderPriceText -> clear();
//    ui -> orderInputOrderStockText -> clear();
//    ui -> orderInputDateText -> clear();

//    return;
//}

void OrderManager::AddObj()
{
    QString clientName, productName, date;
    int clientId, productId, orderPrice, orderStock;

    if(ui -> orderInputIdText->text() != "")
    {
        QMessageBox::information(this, "ID 입력 금지", "신규 주문내역 등록시에는 ID 입력 금지");
        return;
    }
    if(
            ui -> orderInputClientIdText->text() != "" &&
            ui -> orderInputProductIdText->text() != "" &&
            ui -> productInputPriceText->text() != "" &&
            ui -> productInputStockText->text() != "")
    {
        name = ui -> productInputNameText->text();
        brand = ui -> productInputBrandText->text();
        price = ui -> productInputPriceText->text().toInt();
        stock = ui -> productInputStockText->text().toInt();

        QSqlQuery query(productModel->database());
        query.prepare("INSERT INTO client VALUES (seq_product_id.nextval, ?, ?, ?, ?, 0)");
        query.bindValue(1, name);
        query.bindValue(2, brand);
        query.bindValue(3, price);
        query.bindValue(4, stock);
        query.exec();
        productModel->setFilter("isdelete = 0");
        productModel->select();
        ui->productTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    ui -> productInputNameText-> clear();
    ui -> productInputBrandText -> clear();
    ui -> productInputPriceText -> clear();
    ui -> productInputStockText -> clear();
    return;
}

// 주문 정보 삭제
void OrderManager::DelObj()
{
    QTreeWidgetItem* item = ui->orderTreeWidget->currentItem();
    if(item != nullptr) {
        orderList.remove(item->text(0).toInt());
        ui->orderTreeWidget->takeTopLevelItem(ui->orderTreeWidget->indexOfTopLevelItem(item));
        //        delete item;
        ui->orderTreeWidget->update();
        return;
    }
}


// 주문 이력 수정
void OrderManager::ModiObj()
{
    int id;
    int num;
    Order* order;

    if(
            ui -> orderInputClientIdText->text() != "" &&
            ui -> orderInputProductNameText->text() != "" &&
            ui -> orderInputDateText->text() != "" &&
            ui -> orderInputOrderPriceText->text() != "" &&
            ui -> orderInputOrderStockText->text() != "")
    {
        id = (ui -> orderInputIdText->text()).toInt();
        if(orderList.find(id) == orderList.end())
        {
            QMessageBox::information(this, "안내", "해당 하는 ID의 주문 정보가 없습니다.");
            return;
        }
        // 널 포인터 체크 - 존재하지 않는 고객 ID 입력시 널 포인트가 반환될 가능성
        if(CM -> TossObj(ui -> orderInputClientIdText->text().toInt()) == nullptr )
        {
            QMessageBox::information(this, "안내", "수정하고자하는 ID의 고객이 없습니다.");
            return;
        }
        order = orderList.find(id).value();			// 찾아서 클라이언트 객체를 할당
        order -> SetClientId((ui -> orderInputClientIdText->text()).toInt());
        order -> SetProductName(ui -> orderInputProductNameText->text());
        order -> SetOrderStock(ui -> orderInputOrderStockText -> text().toInt());
        order -> SetDate(ui -> orderInputDateText -> text().toInt());
        order -> SetOrderPrice(ui -> orderInputOrderPriceText -> text().toInt());
        order -> SetClientName(CM -> TossObj(order->GetClientId()) -> GetName());
        return;
    }
    else
        QMessageBox::information(this, "안내", "수정하고자 하는 주문 내역을 모두 입력해 주세요.");
    return;
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

Order* OrderManager::TossObj(int id)
{
    Order* order = nullptr;
    if(orderList.find(id) == orderList.end())
    {
        QMessageBox::information(this, "안내", "해당 하는 ID의 주문 정보가 없습니다.");
        return order;
    }
    return order;
}

//선택시 메뉴 열리기

void OrderManager::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->orderTreeWidget->mapToGlobal(pos);
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

