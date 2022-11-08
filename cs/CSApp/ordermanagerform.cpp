#include "ordermanagerform.h"
#include "ui_ordermanagerform.h"
#include "orderitem.h"

#include <QFile>
#include <QMenu>

OrderManagerForm::OrderManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OrderManagerForm)
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

    connect(ui->searchLineEdit, SIGNAL(returnPressed()),
            this, SLOT(on_searchPushButton_clicked()));
}

void OrderManagerForm::loadData()
{
    QFile file("orderlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");
        if(row.size()) {
            int id = row[0].toInt();
            QString cname = ui->clientComboBox->itemText(clientIDList.indexOf(row[1].toInt()));
            QString pname = ui->productComboBox->itemText(productIDList.indexOf(row[2].toInt()));
            OrderItem* c = new OrderItem(id, row[1].toInt(), cname,
                    row[2].toInt(), pname, row[3].toInt(),
                    row[4].toInt(), row[5].toInt());
            ui->treeWidget->addTopLevelItem(c);
            orderList.insert(id, c);
        }
    }
    file.close( );
}

OrderManagerForm::~OrderManagerForm()
{
    delete ui;

    QFile file("orderlist.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (const auto& v : orderList) {
        OrderItem* o = v;
        out << o->id() << ", " << o->getCid() << ", ";
        out << o->getPid() << ", ";
        out << o->getPrice() << ", ";
        out << o->getQuantity() << ", ";
        out << o->getTotalPrice() << "\n";
    }
    file.close( );
}

void OrderManagerForm::addClient(int id, QString name)
{
    clientIDList << id;
    ui->clientComboBox->addItem(name);
}

void OrderManagerForm::addProduct(int id, QString name)
{
    productIDList << id;
    ui->productComboBox->addItem(name);
}

void OrderManagerForm::on_clientComboBox_currentIndexChanged(int index)
{
    emit getClientInfo(clientIDList[index]);
}

void OrderManagerForm::getClientInfo(QString name, QString phoneNumber, QString address)
{
    ui->clientTreeWidget->clear();
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->clientTreeWidget);
    item->setText(0, name);
    item->setText(1, phoneNumber);
    item->setText(2, address);
}

void OrderManagerForm::getProductInfo(QString name, int price, int quantity)     // 응답
{
    ui->productTreeWidget->clear();
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->productTreeWidget);
    item->setText(0, name);
    item->setText(1, QString::number(price));
    item->setText(2, QString::number(quantity));

    ui->priceLineEdit->setText(QString::number(price));

    //    QIntValidator *v = new QIntValidator(0, price, this);
    //    ui->quantityLineEdit->setValidator(v);
    ui->quantitySpinBox->setMaximum(quantity);
}

void OrderManagerForm::on_productComboBox_currentIndexChanged(int index)
{
    emit getProductInfo(productIDList[index]);
}

void OrderManagerForm::on_quantitySpinBox_valueChanged(int arg1)
{
    ui->totalPriceLineEdit->setText(QString::number(arg1 * ui->priceLineEdit->text().toInt()));
}

void OrderManagerForm::removeItem()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if(item != nullptr) {
        orderList.remove(item->text(0).toInt());
        ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));
//        delete item;
        ui->treeWidget->update();
    }
}

void OrderManagerForm::on_treeWidget_customContextMenuRequested(const QPoint &pos)
{
    QPoint globalPos = ui->treeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

void OrderManagerForm::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    emit getClientInfo(clientIDList[ui->clientComboBox->findText(item->text(1))]);
    emit getProductInfo(productIDList[ui->productComboBox->findText(item->text(2))]);
    ui->idLineEdit->setText(item->text(0));
    ui->clientComboBox->setCurrentText(item->text(1));
    ui->productComboBox->setCurrentText(item->text(2));
    ui->priceLineEdit->setText(item->text(3));
    ui->quantitySpinBox->setValue(item->text(4).toInt());
    ui->totalPriceLineEdit->setText(item->text(5));
    ui->toolBox->setCurrentIndex(0);
}

int OrderManagerForm::makeId( )
{
    if(orderList.size( ) == 0) {
        return 300;
    } else {
        auto id = orderList.lastKey();
        return ++id;
    }
}

void OrderManagerForm::on_addPushButton_clicked()
{
    int id = makeId( );
    ui->idLineEdit->setText(QString::number(id));
    int cid, pid, price, quantity, totalPrice;
    cid = clientIDList[ui->clientComboBox->currentIndex()];
    pid = productIDList[ui->productComboBox->currentIndex()];
    price = ui->priceLineEdit->text().toInt();
    quantity = ui->quantitySpinBox->value();
    totalPrice = ui->totalPriceLineEdit->text().toInt();
    QString cname = ui->clientComboBox->itemText(clientIDList.indexOf(cid));
    QString pname = ui->productComboBox->itemText(productIDList.indexOf(pid));
    if(ui->clientComboBox->currentIndex() >= 0) {
        OrderItem* o = new OrderItem(id, cid, cname, pid, pname,
                                     price, quantity, totalPrice);
        ui->treeWidget->addTopLevelItem(o);
        orderList.insert(id, o);
    }
}

void OrderManagerForm::on_modifyPushButton_clicked()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if(item != nullptr) {
        int key = item->text(0).toInt();
        OrderItem* o = orderList[key];

        int cid, pid, price, quantity, totalPrice;
        cid = clientIDList[ui->clientComboBox->currentIndex()];
        pid = productIDList[ui->productComboBox->currentIndex()];
        price = ui->priceLineEdit->text().toInt();
        quantity = ui->quantitySpinBox->value();
        totalPrice = ui->totalPriceLineEdit->text().toInt();
        o->setCid(cid);
        o->setPid(pid);
        o->setPrice(price);
        o->setQuantity(quantity);
        o->setTotalPrice(totalPrice);
        orderList[key] = o;
    }
}

void OrderManagerForm::on_searchPushButton_clicked()
{
    ui->searchTreeWidget->clear();
//    for(int i = 0; i < ui->treeWidget->columnCount(); i++)
    int i = ui->searchComboBox->currentIndex();
    auto flag = (i == 1 || i == 2)? Qt::MatchCaseSensitive|Qt::MatchContains
                                 : Qt::MatchCaseSensitive;
    {
        auto items = ui->treeWidget->findItems(ui->searchLineEdit->text(), flag, i);

        foreach(auto i, items) {
            OrderItem* o = static_cast<OrderItem*>(i);
            int id = o->id();
            int cid = o->getCid();
            int pid = o->getPid();
            int price = o->getPrice();
            int quantity = o->getQuantity();
            int totalPrice = o->getTotalPrice();
            QString cname = ui->clientComboBox->itemText(clientIDList.indexOf(cid));
            QString pname = ui->productComboBox->itemText(productIDList.indexOf(pid));
            OrderItem* item = new OrderItem(id, cid, cname, pid, pname,
                                            price, quantity, totalPrice);
            ui->searchTreeWidget->addTopLevelItem(item);
        }
    }
}

