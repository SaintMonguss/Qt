#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <QWidget>
#include <QString>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <QMap>

#include "Order.h"
#include "clientmanager.h"
#include "productmanager.h"


using std::cout;
using std::cin;
using std::string;
using std::map;

namespace Ui {
class OrderManager;
}

class OrderManager : public QWidget
{
    Q_OBJECT

private:
    QMenu* menu;
    int idHistory;
    Ui::OrderManager *ui;
    QMap<int, Order*> orderList;
    ClientManager* CM;
    ProductManager* PM;

public:
    OrderManager(ClientManager*, ProductManager*);
    ~OrderManager();

private slots:
    void on_orderTreeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void resetSearchResult();

public slots:
    void showContextMenu(const QPoint &);
    void AddObj();
    void DelObj();
    void ModiObj();
    void SerchObj();
    Order* TossObj(int);
};

#endif // ORDERMANAGER_H
