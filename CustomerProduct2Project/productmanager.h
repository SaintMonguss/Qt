#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include <iostream>
#include <QMap>
#include <vector>
#include <fstream>
#include <sstream>
#include <QWidget>
#include <QString>

#include "Product.h"

using std::cout;
using std::cin;
using std::string;
using std::map;

namespace Ui {
class ProductManager;
}

class ProductManager : public QWidget
{
    Q_OBJECT

private:
    int idHistory;
    Ui::ProductManager *ui;
    QMap<int, Product*> productList;
    QMenu* menu;

public:
    explicit ProductManager(QWidget *parent = nullptr);
    ~ProductManager();

    //    std::vector<QString> parseCSV(std::istream& , char);

private slots:
    void on_productTreeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void resetSearchResult();


public slots:
    void showContextMenu(const QPoint &);
    void AddObj();
    void DelObj();
    void ModiObj();
    void SearchObj( );
    Product* TossObj(int);
};

#endif // PRODUCTMANAGER_H

