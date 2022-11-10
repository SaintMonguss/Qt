#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <iostream>
#include <QMap>
#include <vector>
#include <fstream>
#include <sstream>
#include <QWidget>
#include <QString>

#include "Client.h"

using std::cout;
using std::cin;
using std::string;
using std::map;

class QSqlTableModel;
class QSqlDatabase;

namespace Ui {
class ClientManager;
}

class ClientManager : public QWidget
{
    Q_OBJECT

private:
    int idHistory;
    Ui::ClientManager *ui;
    QMap<int, Client*> clientList;
    QMenu* menu;
    QSqlTableModel* clientModel;

public:
    explicit ClientManager(QWidget *parent = nullptr);
    ~ClientManager();
    void loadData(); //저장된 데이터를 불러오기 위한 함수

signals:
    void clientAdded(int, QString);


private slots:
    void on_clientTreeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void resetSearchResult();

public slots:
    void showContextMenu(const QPoint &);
    void AddObj();
    void DelObj();
    void ModiObj();
    void SearchObj( );
    Client* TossObj(int);
};

#endif // CLIENTMANAGER_H
