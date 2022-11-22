#include "productmanager.h"
#include "ui_productmanager.h"

#include <iostream>
#include <QString>
#include <iomanip>
#include <QDebug>
#include <QMessageBox>
#include <QMenu>
#include <QPixmap>
#include <QSqlQuery>
#include <QSqlTableModel>

ProductManager::ProductManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductManager)
{
    ui->setupUi(this);

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(DelObj()));

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->productTreeView->setContextMenuPolicy(Qt::CustomContextMenu);

    //커스텀 슬롯 연결
    connect(ui-> productTreeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui -> productSearchButton, SIGNAL(clicked()), SLOT(SearchObj()));
    connect(ui -> productModifyButton, SIGNAL(clicked()), this, SLOT(ModiObj()));
    connect(ui-> productInputConfirmButton, SIGNAL(clicked()), SLOT(AddObj()));
    connect(ui -> productResetButton, SIGNAL(clicked()), SLOT(resetSearchResult()));
}

    //DB 관련 선언부
void ProductManager::loadData()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "productDBConnection");
    db.setDatabaseName("productlist.db");
    if (db.open( )) {
        QSqlQuery query(db);
        query.exec("CREATE TABLE IF NOT EXISTS product"
                   "(id INTEGER Primary Key AUTOINCREMENT,"
                   "name VARCHAR(40) NOT NULL,"
                   "brand VARCHAR(40) NOT NULL,"
                   "price INTEGER,"
                   "stock INTEGER,"
                   "isdelete BOOLEAN NOT NULL CHECK (isdelete IN (0, 1)));");
        productModel = new QSqlTableModel(nullptr, db);
        productModel->setTable("product");
        productModel->setFilter("isdelete = 0");
        productModel->select();
        productModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        productModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
        productModel->setHeaderData(2, Qt::Horizontal, tr("brand"));
        productModel->setHeaderData(3, Qt::Horizontal, tr("price"));
        productModel->setHeaderData(4, Qt::Horizontal, tr("stock"));

        ui-> productTreeView->setModel(productModel);
        ui -> productTreeView ->setColumnHidden(5 , true);
        ui->productTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
}

ProductManager::~ProductManager()
{
    delete ui;
    QSqlDatabase db = productModel->database();
    if(db.isOpen())
    {
        productModel->submitAll();
        db.close();
    }
}


//상품 정보 추가
void ProductManager::AddObj()
{
    QString name, brand;
    int price, stock;

    if(ui -> productInputIDText->text() != "")
    {
        QMessageBox::information(this, "ID 입력 금지", "신규 상품 등록시에는 ID 입력 금지");
        return;
    }
    if(
            ui -> productInputNameText->text() != "" &&
            ui -> productInputBrandText->text() != "" &&
            ui -> productInputPriceText->text() != "" &&
            ui -> productInputStockText->text() != "")
    {
        name = ui -> productInputNameText->text();
        brand = ui -> productInputBrandText->text();
        price = ui -> productInputPriceText->text().toInt();
        stock = ui -> productInputStockText->text().toInt();
        QSqlDatabase db = QSqlDatabase::database("productDBConnection");
        QSqlQuery query(db);
        query.prepare("INSERT INTO product VALUES (?, ?, ?, ?, ?, 0)");
        query.bindValue(1, name);
        query.bindValue(2, brand);
        query.bindValue(3, price);
        query.bindValue(4, stock);
        query.exec();
        qDebug() << "대체 뭐임";
        productModel->setFilter("isdelete = 0");
        productModel->select();
        ui->productTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

        ui -> productInputNameText-> clear();
        ui -> productInputBrandText -> clear();
        ui -> productInputPriceText -> clear();
        ui -> productInputStockText -> clear();
        return;
    }
    QMessageBox::information(this, "미기입 정보", "ID를 제외한 모든 정보를 입력해 주세요");
    return;
}

//상품 정보 삭제
void ProductManager::DelObj()
{
    QModelIndex index = ui -> productTreeView -> currentIndex();
    if(index.isValid())
    {
        productModel->setData(index.siblingAtColumn(5), 1);
        productModel -> submit();
        productModel->select();

        ui->productTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
}

//상품 정보 수정
void ProductManager::ModiObj()
{
    if(
            ui -> productInputIDText->text() != "" &&
            ui -> productInputNameText->text() != "" &&
            ui -> productInputBrandText->text() != "" &&
            ui -> productInputPriceText->text() != "" &&
            ui -> productInputStockText->text() != "")
    {
        QModelIndex index = ui->productTreeView->currentIndex();
        if(index.isValid())
        {
            QString name, brand;
            int price, stock;
            name = ui-> productInputNameText->text();
            brand = ui-> productInputBrandText->text();
            price = ui-> productInputPriceText->text().toInt();
            stock = ui -> productInputStockText->text().toInt();

            productModel->setData(index.siblingAtColumn(1), name);
            productModel->setData(index.siblingAtColumn(2), brand);
            productModel->setData(index.siblingAtColumn(3), price);
            productModel->setData(index.siblingAtColumn(4), stock);
            productModel->submit();
            productModel->select();

            ui->productTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
        }
        else
            QMessageBox::information(this, "안내", "수정 하고자 하는 상품의 모든 정보를 입력해 주세요.");
        return;
    }
}

//상품 정보 검색
void ProductManager::SearchObj()
{
    QString target = ui-> productComboBox->currentText();
    QString search = ui-> productSearchText->text();
    if (target == tr("ID"))
    {
        productModel -> setFilter(QString("isdelete = 0 and id like '%%1%'").arg(search.toInt()));
        productModel -> select();
        ui->productTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    if (target == tr("name"))
    {
        productModel -> setFilter(QString("isdelete = 0 and name like '%%1%'").arg(search));
        productModel -> select();
        ui->productTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    if (target == tr("brand"))
    {
        productModel -> setFilter(QString("isdelete = 0 and brand like '%%1%'").arg(search));
        productModel -> select();
        ui->productTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    if (target == tr("price"))
    {
        productModel -> setFilter(QString("isdelete = 0 and price = '%%1%'").arg(search.toInt()));
        productModel -> select();
        ui->productTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    if (target == tr("stock"))
    {
        productModel -> setFilter(QString("isdelete = 0 and stock = '%%1%'").arg(search.toInt()));
        productModel -> select();
        ui->productTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    return;
}

//상품 한명의 정보를 리턴하는 함수
void ProductManager::acceptProductInfoRequest(int orderId, int productId)
{
    QModelIndexList indexes = productModel->match(productModel->index(0, 0), Qt::EditRole, productId, -1, Qt::MatchFlags(Qt::MatchCaseSensitive));

    foreach(auto index, indexes) {
        QString name = productModel->data(index.siblingAtColumn(1)).toString();
        QString brand = productModel->data(index.siblingAtColumn(2)).toString();
        int price = productModel->data(index.siblingAtColumn(3)).toInt();
        int stock = productModel->data(index.siblingAtColumn(4)).toInt();

        emit sendProductInfo(orderId, name, brand, price, stock);
    }
}
//선택시 메뉴 열리기

void ProductManager::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->productTreeView->mapToGlobal(pos);
    menu->exec(globalPos);
}

//선택한 항목 속성 값 라인에디터에 표시
void ProductManager::on_productTreeView_clicked(const QModelIndex &index)
{
    QString id = productModel->data(index.siblingAtColumn(0)).toString();
    QString name = productModel->data(index.siblingAtColumn(1)).toString();
    QString brand = productModel->data(index.siblingAtColumn(2)).toString();
    QString price = productModel->data(index.siblingAtColumn(3)).toString();
    QString stock = productModel->data(index.siblingAtColumn(4)).toString();

    ui->productInputIDText->setText(id);
    ui->productInputNameText->setText(name);
    ui->productInputBrandText->setText(brand);
    ui->productInputPriceText->setText(price);
    ui->productInputStockText->setText(stock);
}


void ProductManager::resetSearchResult()
{
    ui -> productSearchText-> clear();
    productModel->setFilter("isdelete = 0");
    productModel->select();
    ui->productTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}
