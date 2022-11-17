#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <iostream>
#include <QWidget>
#include <QString>

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
    Ui::ClientManager *ui;
    QMenu* menu;
    QSqlTableModel* clientModel;

public:
    explicit ClientManager(QWidget *parent = nullptr);
    ~ClientManager();
    void loadData(); //저장된 데이터를 불러오기 위한 함수

signals:
    void clientAdded(int, QString);
    void sendClientInfo(int, QString, QString, QString, QString);

private slots:
    void resetSearchResult();
    void on_clientTreeView_clicked(const QModelIndex &index);

public slots:
    void showContextMenu(const QPoint &);
    void AddObj();
    void DelObj();
    void ModiObj();
    void SearchObj( );
    void acceptClientInfoRequest(int, int);
};

#endif // CLIENTMANAGER_H
