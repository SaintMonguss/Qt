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
    void AddObj();
    void DelObj(int );
    void ModiObj(int , QString , QString , QString , QString);
    void SerchObj(int );
    void SerchObj(QString , QString);
    Client* TossObj(int);

private:
    Ui::ClientManager *ui;
    QMap<int, Client*> clientList;
};

#endif // CLIENTMANAGER_H
