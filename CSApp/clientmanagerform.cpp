#include "clientmanagerform.h"
#include "ui_clientmanagerform.h"
#include "clientitem.h"

#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <QMenu>

ClientManagerForm::ClientManagerForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientManagerForm)
{
    ui->setupUi(this);

    QAction* removeAction = new QAction("&Remove");
    connect(removeAction, SIGNAL(triggered()), SLOT(removeItem()));

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    ifstream file;
    file.open("clientlist.txt");
    if(!file.fail()) {
        while(!file.eof()) {
            vector<string> row = parseCSV(file, ',');
            if(row.size()) {
                int id = stoi(row[0]);
                ClientItem* c = new ClientItem(id, row[1], row[2], row[3]);
                ui->treeWidget->addTopLevelItem(c);
                clientList.insert(id, c);
            }
        }
    }
    file.close( );
}

ClientManagerForm::~ClientManagerForm()
{
    delete ui;

    ofstream file;
    file.open("clientlist.txt");
    if(!file.fail()) {
        for (const auto& v : clientList) {
            ClientItem* c = v;
            file << c->id() << ", " << c->getName() << ", ";
            file << c->getPhoneNumber() << ", ";
            file << c->getAddress() << endl;
        }
    }
    file.close( );
}

ClientItem* ClientManagerForm::search(int id)
{
    return clientList[id];
}

int ClientManagerForm::makeId( )
{
    if(clientList.size( ) == 0) {
        return 100;
    } else {
        auto id = clientList.lastKey();
        return ++id;
    }
}

vector<string> ClientManagerForm::parseCSV(istream &file, char delimiter)
{
    stringstream ss;
    vector<string> row;
    string t = " \n\r\t";

    while(!file.eof()) {
        char c = file.get();
        if (c==delimiter || c=='\r' || c=='\n') {
            if(file.peek()=='\n') file.get();
            string s = ss.str();
            s.erase(0, s.find_first_not_of(t));
            s.erase(s.find_last_not_of(t)+1);
            row.push_back(s);
            ss.str("");
            if (c!=delimiter) break;
        } else {
            ss << c;
        }
    }
    return row;
}

void ClientManagerForm::removeItem()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if(item != nullptr) {
        clientList.remove(item->text(0).toInt());
        ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(item));
//        delete item;
        ui->treeWidget->update();
    }
}

void ClientManagerForm::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->treeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

void ClientManagerForm::on_searchPushButton_clicked()
{
    auto items = ui->treeWidget->findItems(ui->searchLineEdit->text(), Qt::MatchCaseSensitive);

    ui->searchTreeWidget->clear();
    foreach(auto i, items) {
        ClientItem* c = static_cast<ClientItem*>(i);
        int id = c->id();
        string name = c->getName();
        string number = c->getPhoneNumber();
        string address = c->getAddress();
        ClientItem* item = new ClientItem(id, name, number, address);
        ui->searchTreeWidget->addTopLevelItem(item);
    }
}

void ClientManagerForm::on_modifyPushButton_clicked()
{
    QTreeWidgetItem* item = ui->treeWidget->currentItem();
    if(item != nullptr) {
        int key = item->text(0).toInt();
        ClientItem* c = search(key);
        string name, number, address;
        name = ui->nameLineEdit->text().toUtf8();   // QString --> string
        number = ui->phoneNumberLineEdit->text().toUtf8();
        address = ui->addressLineEdit->text().toUtf8();
        c->setName(name);
        c->setPhoneNumber(number);
        c->setAddress(address);
        clientList[key] = c;
    }
}

void ClientManagerForm::on_addPushButton_clicked()
{
    string name, number, address;
    int id = makeId( );
    name = ui->nameLineEdit->text().toUtf8();
    number = ui->phoneNumberLineEdit->text().toUtf8();
    address = ui->addressLineEdit->text().toUtf8();
    if(name.length()) {
        ClientItem* c = new ClientItem(id, name, number, address);
        clientList.insert(id, c);
        ui->treeWidget->addTopLevelItem(c);
    }
}

void ClientManagerForm::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui->idLineEdit->setText(item->text(0));
    ui->nameLineEdit->setText(item->text(1));
    ui->phoneNumberLineEdit->setText(item->text(2));
    ui->addressLineEdit->setText(item->text(3));
}

