#include <iostream>
#include <QString>
#include <iomanip>
#include <stdio.h>
#include <QDebug>
#include <QFile>
#include <QMap>
#include <QMessageBox>
#include <QMenu>
#include <QPixmap>

#include "Product.h"
#include "productmanager.h"
#include "ui_productmanager.h"

ProductManager::ProductManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductManager)
{
    ui->setupUi(this);

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(DelObj()));

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->productTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui-> productTreeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui -> productSearchButton, SIGNAL(clicked()), SLOT(SearchObj()));
    connect(ui -> productModifyButton, SIGNAL(clicked()), this, SLOT(ModiObj()));
    connect(ui-> productInputConfirmButton, SIGNAL(clicked()), SLOT(AddObj()));
    connect(ui -> productResetButton, SIGNAL(clicked()), SLOT(resetSearchResult()));

    QFile file("productlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    idHistory = in.readLine().toInt(); // 아이디 히스토리 유지
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");
        if(row.size()) {
            int id = row[0].toInt();
            Product* p = new Product(id, row[1], row[2], row[3].toInt(), row[4].toInt());
            ui -> productTreeWidget ->addTopLevelItem(p);
            productList.insert(id, p);
        }
    }
    file.close( );
}

ProductManager::~ProductManager()
{
    delete ui;

    //파일 저장
    QFile file("productlist.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << idHistory << "\n";
    for (const auto& v : productList) {
        Product* p = v;
        out << QString::number(p->GetId()) << ", ";
        out << p->GetName() << ", ";
        out << p->GetBrand() << ", ";
        out << QString::number(p->GetPrice()) << ", ";
        out << QString::number(p->GetStock()) << "\n";
    }
    file.close( );
}


//고객 정보 추가
void ProductManager::AddObj()
{
    Product* product;
    int id;

    if(ui -> productInputIDText->text() != "")
    {
        QMessageBox::information(this, "임의의 ID 입력 감지", "새 상품 등록시에는 ID 입력 금지");
        return;
    }

    if (productList.empty())
    {
        idHistory  = id = 1;
    }
    else
    {
        id = idHistory + 1;
        idHistory += 1;
    }
    if(
            ui -> productInputNameText->text() != "" &&
            ui -> productInputBrandText->text() != "" &&
            ui -> productInputPriceText->text() != "" &&
            ui -> productInputStockText->text() != "")
    {
        product = new Product(id);
        product->SetName(ui -> productInputNameText->text());
        product->SetBrand(ui -> productInputBrandText -> text());
        product->SetPrice(ui -> productInputPriceText -> text().toInt());
        product->SetStock(ui -> productInputStockText -> text().toInt());
        productList.insert(id, product );
        ui -> productTreeWidget ->addTopLevelItem(product);
        ui -> productTreeWidget -> update();
        return;
    }

    ui -> productInputNameText-> clear();
    ui -> productInputBrandText -> clear();
    ui -> productInputPriceText -> clear();
    ui -> productInputStockText -> clear();

    return;
}

// 고객 정보 삭제
void ProductManager::DelObj()
{
    QTreeWidgetItem* item = ui->productTreeWidget->currentItem();
    if(item != nullptr) {
        productList.remove(item->text(0).toInt());
        ui->productTreeWidget->takeTopLevelItem(ui->productTreeWidget->indexOfTopLevelItem(item));
//        delete item;
        ui->productTreeWidget->update();
        return;
    }
}

// 고객 정보 수정
void ProductManager::ModiObj()
{
    int id;
    Product* product;
    if(
            ui -> productInputIDText->text() != "" &&
            ui -> productInputNameText->text() != "" &&
            ui -> productInputBrandText->text() != "" &&
            ui -> productInputPriceText->text() != "" &&
            ui -> productInputStockText->text() != "")
    {
        id = (ui -> productInputIDText->text()).toInt();
        if(productList.find(id) == productList.end())
        {
            QMessageBox::information(this, "안내", "해당 하는 ID의 상품이 없습니다.");
            return;
        }

        product = productList.find(id).value();			// 찾아서 클라이언트 객체를 할당
        product->SetName(ui -> productInputNameText->text());
        product->SetBrand(ui -> productInputBrandText->text());
        product->SetPrice(ui -> productInputPriceText->text().toInt());
        product->SetStock(ui -> productInputStockText->text().toInt());
        return;
    }
    else
        QMessageBox::information(this, "안내", "수정 하고자 하는 상품의 모든 정보를 입력해 주세요.");
    return;

}

// 고객 정보 검색
void ProductManager::SearchObj()
{;
    QString target = ui-> productComboBox->currentText();
    if (target == tr("ID"))
        for (auto itr = productList.begin(); itr != productList.end(); itr++)
        {
            if (itr.value()->GetId() == ui-> productSearchText->text().toInt())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == tr("name"))
        for (auto itr = productList.begin(); itr != productList.end(); itr++)
        {
            if (itr.value()->GetName() == ui->productSearchText->text())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == tr("brand"))
        for (auto itr = productList.begin(); itr != productList.end(); itr++)
        {
            if (itr.value()->GetBrand() == ui->productSearchText -> text())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == tr("price"))
        for (auto itr = productList.begin(); itr != productList.end(); itr++)
        {
            if (itr.value()->GetPrice() == ui -> productSearchText -> text().toInt())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == tr("stock"))
        for (auto itr = productList.begin(); itr != productList.end(); itr++)
        {
            if (itr.value()->GetStock() == ui -> productSearchText ->text().toInt())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    return;
}



//고객 한명의 정보를 리턴하는 함수
Product* ProductManager::TossObj(int id)
{
    Product* product =nullptr;
    try
    {
        if(productList.find(id) == productList.end())
            throw;
    }
    catch (...)
    {
        qDebug() << "해당하는 ID 없음";
        return product;
    }
    product = productList.find(id).value();
    return product;
}
//선택시 메뉴 열리기

void ProductManager::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->productTreeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

//선택한 항목 속성 값 라인에디터에 표시
void ProductManager::on_productTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui->productInputIDText->setText(item->text(0));
    ui->productInputNameText->setText(item->text(1));
    ui->productInputBrandText->setText(item->text(2));
    ui->productInputPriceText->setText(item->text(3));
    ui->productInputStockText->setText(item->text(4));
}

void ProductManager::resetSearchResult()
{
    ui -> productSearchText-> clear();
    for (auto itr = productList.begin(); itr != productList.end(); itr++)
    {
        itr.value()->setHidden(false);
    }
}
