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

namespace Ui {
class ClientManager;
}

class ClientManager : public QWidget
{
    Q_OBJECT

public:
    explicit ClientManager(QWidget *parent = nullptr);
    ~ClientManager();

    //    std::vector<QString> parseCSV(std::istream& , char);

public slots:
    void showContextMenu(const QPoint &);
    void AddObj();
    void DelObj();
    void ModiObj();
    void SerchObj(int );
    void SerchObj(QString , QString);
    Client* TossObj(int);

private slots:
    void on_clientTreeWidget_itemClicked(QTreeWidgetItem *item, int column);

private:
    int idHistory;
    Ui::ClientManager *ui;
    QMap<int, Client*> clientList;
    QMenu* menu;
};

#endif // CLIENTMANAGER_H
