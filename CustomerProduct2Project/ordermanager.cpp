#include "ordermanager.h"
#include "ui_clientmanager.h"
#include "ui_ordermanager.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <windows.h>
#include <QFile>
#include <QMap>
#include <QMessageBox>
#include <QMenu>

// 생성자 파일 불러오기
OrderManager::OrderManager(ClientManager* CM, ProductManager* PM) : CM(CM), PM(PM) ,
    ui(new Ui::OrderManager)
{
    ui->setupUi(this);

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(DelObj()));

    menu = new QMenu;
    menu -> addAction(removeAction);
    ui -> orderTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui -> orderTreeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui -> orderSearchButton, SIGNAL(clicked()), SLOT(SearchObj()));
    connect(ui -> orderModifyButton, SIGNAL(clicked()), this, SLOT(ModiObj()));
    connect(ui -> orderInputConfirmButton, SIGNAL(clicked()), SLOT(AddObj()));
    connect(ui -> orderResetButton, SIGNAL(clicked()), SLOT(resetSearchResult()));

    QFile file("orderlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    idHistory = in.readLine().toInt(); // 아이디 히스토리 유지
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");
        if (row.size()) {
            int id = row[0].toInt();
            QString productName = row[1];
            QString clientName = row[2];
            int date = row[3].toInt();
            int clientId = row[4].toInt();
            int orderPrice = row[5].toInt();
            int orderStock = row[6].toInt();
            Order* c = new Order(id, productName, clientName, date, clientId, orderPrice, orderStock);
            orderList.insert( id, c );
        }
    }
    file.close();
};

//소멸자 파일 저장
OrderManager::~OrderManager()
{
    delete ui;

    //파일 저장
    QFile file("orderlist.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    out << idHistory << "\n";
        for (const auto& v : orderList) {
            Order* c = v;
            out << QString::number(c -> GetOrderId()) << ", ";
            out << c -> GetProductName() << ", ";
            out << c -> GetClientName() << ", ";
            out << QString::number(c -> GetDate()) << ", ";
            out << QString::number(c->GetClientId()) << ", ";
            out << QString::number(c->GetOrderPrice()) << ", ";
            out << QString::number(c->GetOrderStock()) << "\n";
        }
    file.close();
}



//주문 정보 추가
void OrderManager::AddObj()
{
    Order* order;
    int id;

    if(ui -> orderInputIdText->text() != "")
    {
        QMessageBox::information(this, "ID 입력 금지", "신규 주문 등록시에는 ID 입력 금지");
        return;
    }
    if(
            ui -> orderInputClientIdText->text() != "" &&
            ui -> orderInputProductNameText->text() != "" &&
            ui -> orderInputDateText->text() != "" &&
            ui -> orderInputOrderPriceText->text() != "" &&
            ui -> orderInputOrderStockText->text() != ""
            )
    {
        // 널 포인터 체크 - 존재하지 않는 고객 ID 입력시 널 포인트가 반환될 가능성
        if(CM -> TossObj(ui -> orderInputClientIdText->text().toInt()) == nullptr )
        {
            QMessageBox::information(this, "안내", "해당 하는 ID의 고객이 없습니다.");
            return;
        }
        if (orderList.empty())
        {
            idHistory  = id = 1;
        }
        else
        {
            id = idHistory + 1;
            idHistory += 1;
        }
        order = new Order(id);
        order -> SetClientId((ui -> orderInputClientIdText->text()).toInt());
        order -> SetProductName(ui -> orderInputProductNameText->text());
        order -> SetOrderStock(ui -> orderInputOrderStockText -> text().toInt());
        order -> SetDate(ui -> orderInputDateText -> text().toInt());
        order -> SetOrderPrice(ui -> orderInputOrderPriceText -> text().toInt());
        order -> SetOrderStock(ui -> orderInputOrderStockText -> text().toInt());

        order -> SetClientName(CM -> TossObj(order->GetClientId()) -> GetName());

        orderList.insert(id, order);
        ui -> orderTreeWidget ->addTopLevelItem(order);
        ui -> orderTreeWidget -> update();
        return;
    }
    ui -> orderInputClientIdText-> clear();
    ui -> orderInputProductNameText -> clear();
    ui -> orderInputOrderStockText -> clear();
    ui -> orderInputOrderPriceText -> clear();
    ui -> orderInputOrderStockText -> clear();
    ui -> orderInputDateText -> clear();

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
        order -> SetOrderStock(ui -> orderInputOrderStockText -> text().toInt());
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
    if (target == "tr(\"orderID\")")
        for (auto itr = orderList.begin(); itr != orderList.end(); itr++)
        {
            if (itr.value()-> GetOrderId() == ui-> orderSearchOrderIdText -> text().toInt())
                itr.value()-> setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == "tr(\"clientName\")")
        for (auto itr = orderList.begin(); itr != orderList.end(); itr++)
        {
            if (itr.value()->GetClientName() == ui -> orderSearchclientNameText -> text())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == "tr(\"clientID\")")
        for (auto itr = orderList.begin(); itr != orderList.end(); itr++)
        {
            if (itr.value()->GetClientId() == ui -> orderSearchclientIdText -> text().toInt())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == "tr(\"productName\")")
        for (auto itr = orderList.begin(); itr != orderList.end(); itr++)
        {
            if (itr.value()->GetProductName() == ui -> orderSearchProductNameText -> text())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == "tr(\"date\")")
        for (auto itr = orderList.begin(); itr != orderList.end(); itr++)
        {
            if (itr.value()->GetDate() == ui -> orderSearchDateText ->text().toInt())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == "tr(\"orderPrice\")")
        for (auto itr = orderList.begin(); itr != orderList.end(); itr++)
        {
            if (itr.value()->GetOrderPrice() == ui -> orderSearchOrderPriceText ->text().toInt())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == "tr(\"orderStock\")")
        for (auto itr = orderList.begin(); itr != orderList.end(); itr++)
        {
            if (itr.value()->GetOrderStock() == ui -> orderSearchOrderStockText ->text().toInt())
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
    ui -> orderInputProductNameText -> setText(item->text(1));
    ui -> orderInputClientIdText -> setText(item->text(2));
    ui -> orderInputDateText -> setText(item->text(3));
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
