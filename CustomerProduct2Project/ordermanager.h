#ifndef ORDERMANAGER_H
#define ORDERMANAGER_H

#include <QWidget>
#include <QString>
#include <iostream>

using std::cout;
using std::cin;
using std::string;

class QSqlTableModel;
class QSqlDatabase;

namespace Ui {
class OrderManager;
}

class OrderManager : public QWidget
{
    Q_OBJECT

private:
    QMenu* menu;
    Ui::OrderManager *ui;
    QSqlTableModel* orderModel;

public:
    explicit OrderManager(QWidget *parent = nullptr);
    ~OrderManager();
    void loadData();

signals:
    void requestClientInfo(int, int); //clientManager 에게 정보 요청
    void requestProductInfo(int, int); //productManager 에게 정보 요청

private slots:
    void resetSearchResult();
    void on_orderTreeView_clicked(const QModelIndex &index);

public slots:
    void showContextMenu(const QPoint &);
    void AddObj();
    void DelObj();
    void ModiObj();
    void SearchObj();
    void receiveClientInfo(int, QString, QString, QString, QString);
    void receiveProductInfo(int, QString, QString, int, int);
};

#endif // ORDERMANAGER_H
