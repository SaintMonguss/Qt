#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include <iostream>
#include <QWidget>
#include <QString>

using std::cout;
using std::cin;
using std::string;

class QSqlTableModel;
class QSqlDatabase;

namespace Ui {
class ProductManager;
}

class ProductManager : public QWidget
{
    Q_OBJECT

private:
    Ui::ProductManager *ui;
    QMenu* menu;
    QSqlTableModel* productModel;

public:
    explicit ProductManager(QWidget *parent = nullptr);
    ~ProductManager();
    void loadData();

signals:
    void sendProductInfo(int, QString, QString, int, int);

private slots:
    void resetSearchResult();
    void on_productTreeView_clicked(const QModelIndex &index);

public slots:
    void showContextMenu(const QPoint &);
    void AddObj();
    void DelObj();
    void ModiObj();
    void SearchObj( );
    void acceptProductInfoRequest(int, int);
};

#endif // PRODUCTMANAGER_H

