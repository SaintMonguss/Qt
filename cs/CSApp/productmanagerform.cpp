#include "productmanagerform.h"
#include "ui_productmanagerform.h"
#include "produceitem.h"

#include <QFile>
#include <QMenu>

ProductManagerForm::ProductManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ProductManagerForm)
{
    ui->setupUi(this);

    QList<int> sizes;
    sizes << 540 << 400;
    ui->splitter->setSizes(sizes);

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

//    QRegularExpression re("^[0-9]\\d{0,100}$");
//    QRegularExpressionValidator v(re, 0);
//    ui->priceLineEdit->setValidator(&v);
    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));
}

void ProductManagerForm::loadData()
{
    QFile file("productlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");
        if(row.size()) {
            int id = row[0].toInt();
            ProduceItem* c = new ProduceItem(id, row[1], row[2].toInt(), row[3].toInt());
            ui->treeWidget->addTopLevelItem(c);
            productList.insert(id, c);
            emit productAdded(id, row[1]);
        }
    }
    file.close( );
}

ProductManagerForm::~ProductManagerForm()
{
    delete ui;

    QFile file("productlist.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (const auto& v : productList) {
        ProduceItem* c = v;
        out << c->id() << ", " << c->getName() << ", ";
        out << c->getPrice() << ", ";
        out << c->getQuantity() << "\n";
    }
    file.close( );
}

int ProductManagerForm::makeId( )
{
    if(productList.size( ) == 0) {
        return 200;
    } else {
        auto id = productList.lastKey();
        return ++id;
    }
}

void ProductManagerForm::removeItem()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if(item != nullptr) {
        productList.remove(item->text(0).toInt());
        ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));
//        delete item;
        ui->treeWidget->update();
    }
}

void ProductManagerForm::on_addPushButton_clicked()
{
    int id = makeId( );
    ui->idLineEdit->setText(QString::number(id));
    QString name;
    int price, quantity;
    name = ui->nameLineEdit->text();
    price = ui->priceLineEdit->text().toInt();
    quantity = ui->quantitySpinBox->value();
    if(name.length()) {
        ProduceItem* c = new ProduceItem(id, name, price, quantity);
        ui->treeWidget->addTopLevelItem(c);
        productList.insert(id, c);
        emit productAdded(id, name);
    }
}

void ProductManagerForm::on_modifyPushButton_clicked()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if(item != nullptr) {
        int key = item->text(0).toInt();
        ProduceItem* c = productList[key];
        QString name;
        int price, quantity;
        name = ui->nameLineEdit->text();
        price = ui->priceLineEdit->text().toInt();
        quantity = ui->quantitySpinBox->value();
        c->setName(name);
        c->setPrice(price);
        c->setQuantity(quantity);
        productList[key] = c;
    }
}

void ProductManagerForm::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    QPoint globalPos = ui->treeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

void ProductManagerForm::on_searchPushButton_clicked()
{
    ui->searchTreeWidget->clear();
//    for(int i = 0; i < ui->treeWidget->columnCount(); i++)
    int i = ui->searchComboBox->currentIndex();
    auto flag = (i)? Qt::MatchCaseSensitive|Qt::MatchContains
                   : Qt::MatchCaseSensitive;
    {
        auto items = ui->treeWidget->findItems(ui->searchLineEdit->text(), flag, i);

        foreach(auto i, items) {
            ProduceItem* c = static_cast<ProduceItem*>(i);
            int id = c->id();
            QString name = c->getName();
            int price = c->getPrice();
            int quantity = c->getQuantity();
            ProduceItem* item = new ProduceItem(id, name, price, quantity);
            ui->searchTreeWidget->addTopLevelItem(item);
        }
    }
}

void ProductManagerForm::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui->idLineEdit->setText(item->text(0));
    ui->nameLineEdit->setText(item->text(1));
    ui->priceLineEdit->setText(item->text(2));
    ui->quantitySpinBox->setValue(item->text(3).toInt());
    ui->toolBox->setCurrentIndex(0);
}

void ProductManagerForm::acceptProductInfo(int key)
{
    ProduceItem* p = productList[key];
    emit sendProductInfo(p->getName(), p->getPrice(), p->getQuantity());
}

