#include "clientmanager.h"
#include "ui_clientmanager.h"

#include <iostream>
#include <QString>
#include <iomanip>
#include <QDebug>
#include <QMessageBox>
#include <QMenu>
#include <QPixmap>
#include <QSqlQuery>
#include <QSqlTableModel>

ClientManager::ClientManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientManager)
{

    ui->setupUi(this);

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(DelObj()));

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->clientTreeView->setContextMenuPolicy(Qt::CustomContextMenu);
    //커스텀 슬롯 연결부
    connect(ui-> clientTreeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui -> clientSearchButton, SIGNAL(clicked()), SLOT(SearchObj()));
    connect(ui -> clientModifyButton, SIGNAL(clicked()), this, SLOT(ModiObj()));
    connect(ui-> clientInputConfirmButton, SIGNAL(clicked()), SLOT(AddObj()));
    connect(ui -> clientResetButton, SIGNAL(clicked()), SLOT(resetSearchResult()));

}

ClientManager::~ClientManager()
{
    delete ui;
    QSqlDatabase db = clientModel->database();
    if(db.isOpen())
    {
        clientModel->submitAll();
        db.close();
    }
}

//생성자에서 진행시 chatserver와 연동의 서순 문제가 발생, 멤버함수로 구현
// DB관련 구현부
void ClientManager::loadData()
{
    QSqlDatabase db = QSqlDatabase::database();
    db.setDatabaseName("clientlist.db");
    if (db.open( )) {
        QSqlQuery query(db);
        query.exec("CREATE TABLE IF NOT EXISTS client"
                   "(id INTEGER Primary Key,"
                   "name VARCHAR(20) NOT NULL,"
                   "phoneNumber VARCHAR(20) NOT NULL,"
                   "address VARCHAR(50),"
                   "email VARCHAR(20),"
                   "iswithdrow BOOLEAN NOT NULL CHECK (iswithdrow IN (0, 1);");
        //ID값 시퀀스 선언
        // 버그 가능성 있음
        query.exec("CREATE SEQUENCE IF NOT EXISTS seq_client_id"
                   "INCREMENT BY 1 "
                   "START WITH 1 ;");
        clientModel = new QSqlTableModel();
        clientModel->setTable("client");
        clientModel->setFilter("iswithdrow = 0");
        clientModel->select();
        clientModel->setHeaderData(0, Qt::Horizontal, tr("ID"));
        clientModel->setHeaderData(1, Qt::Horizontal, tr("Name"));
        clientModel->setHeaderData(2, Qt::Horizontal, tr("Phone Number"));
        clientModel->setHeaderData(3, Qt::Horizontal, tr("Address"));
        clientModel->setHeaderData(4, Qt::Horizontal, tr("Email"));

        ui-> clientTreeView->setModel(clientModel);
        ui->clientTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    for(int i = 0; i < clientModel->rowCount(); i++)
    {
        int id = clientModel->data(clientModel->index(i, 0)).toInt();
        QString name = clientModel->data(clientModel->index(i, 1)).toString();
        //clientList.insert(id, clientModel->index(i, 0));
        emit clientAdded(id, name);
    }
}


//고객 정보 추가
void ClientManager::AddObj()
{
    QString name, phonNumber, address, email;
    int id;

    if(ui -> clientInputIDText->text() != "")
    {
        QMessageBox::information(this, "ID 입력 금지", "신규 고객 등록시에는 ID 입력 금지");
        return;
    }
    if(
            ui -> clientInputNameText->text() != "" &&
            ui -> clientInputPHText->text() != "" &&
            ui -> clientInputAddressText->text() != "" &&
            ui -> clientInputEmailText->text() != "")
    {
        name = ui -> clientInputNameText->text();
        phonNumber = ui -> clientInputPHText->text();
        address = ui -> clientInputAddressText->text();
        email = ui -> clientInputEmailText->text();

        QSqlQuery query(clientModel->database());
        query.prepare("INSERT INTO client VALUES (seq_client_id.nextval, ?, ?, ?, ?, 0)");
        query.bindValue(1, name);
        query.bindValue(2, phonNumber);
        query.bindValue(3, address);
        query.bindValue(4, email);
        id = query.boundValue(0).toInt();
        query.exec();
        clientModel->setFilter("iswithdrow = 0");
        clientModel->select();
        ui->clientTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
        emit clientAdded(id, ui -> clientInputNameText->text());
    }
    ui -> clientInputNameText-> clear();
    ui -> clientInputPHText -> clear();
    ui -> clientInputAddressText -> clear();
    ui -> clientInputEmailText -> clear();
    return;
}

// 고객 정보 삭제
void ClientManager::DelObj()
{
    QModelIndex index = ui->clientTreeView->currentIndex();
    if(index.isValid())
    {
        clientModel->setData(index.siblingAtColumn(5), 1);
        clientModel->select();
        ui->clientTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
}

// 고객 정보 수정
void ClientManager::ModiObj()
{
    if(
            ui -> clientInputIDText->text() != "" &&
            ui -> clientInputNameText->text() != "" &&
            ui -> clientInputPHText->text() != "" &&
            ui -> clientInputAddressText->text() != "" &&
            ui -> clientInputEmailText->text() != "")
    {
        QModelIndex index = ui->clientTreeView->currentIndex();
        if(index.isValid())
        {
            QString name, phonNumber, address, email;
            name = ui->clientInputNameText->text();
            phonNumber = ui->clientInputPHText->text();
            address = ui-> clientInputAddressText ->text();
            email = ui -> clientInputEmailText->text();

            clientModel->setData(index.siblingAtColumn(1), name);
            clientModel->setData(index.siblingAtColumn(2), phonNumber);
            clientModel->setData(index.siblingAtColumn(3), address);
            clientModel->setData(index.siblingAtColumn(4), email);
            clientModel->submit();
            clientModel->select();

            ui->clientTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
        }
    }
    else
        QMessageBox::information(this, "안내", "수정 하고자 하는 고객의 모든 정보를 입력해 주세요.");
    return;

}

// 고객 정보 검색
void ClientManager::SearchObj()
{
    QString target = ui-> clientComboBox->currentText();
    QString search = ui->clientSearchText->text();
    if (target == tr("ID"))
    {
        clientModel -> setFilter(QString("iswithdrow = 0 and id like '%%1%'").arg(search.toInt()));
        clientModel -> select();
        ui->clientTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    if (target == tr("name"))
    {
        clientModel -> setFilter(QString("iswithdrow = 0 and name like '%%1%'").arg(search));
        clientModel -> select();
        ui->clientTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    if (target == tr("phoneNumber"))
    {
        clientModel -> setFilter(QString("iswithdrow = 0 and phoneNumber like '%%1%'").arg(search));
        clientModel -> select();
        ui->clientTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    if (target == tr("address"))
    {
        clientModel -> setFilter(QString("iswithdrow = 0 and address like '%%1%'").arg(search));
        clientModel -> select();
        ui->clientTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    if (target == tr("E-mail"))
    {
        clientModel -> setFilter(QString("iswithdrow = 0 and email like '%%1%'").arg(search));
        clientModel -> select();
        ui->clientTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    }
    return;
}

//고객 한명의 정보를 리턴하는 함수
void ClientManager::acceptClientInfoRequest(int orderId, int clientId)
{
    QModelIndexList indexes = clientModel->match(clientModel->index(0, 0), Qt::EditRole, id, -1, Qt::MatchFlags(Qt::MatchCaseSensitive));

    foreach(auto index, indexes) {
//    QModelIndex index = clientList[key];
        QString name = clientModel->data(index.siblingAtColumn(1)).toString();
        QString phoneNumber = clientModel->data(index.siblingAtColumn(2)).toString();
        QString address = clientModel->data(index.siblingAtColumn(3)).toString();
        QString email = clientModel->data(index.siblingAtColumn(4)).toString();

        emit sendClientInfo(orderId, name, phoneNumber, address, email);
    }
}
//선택시 메뉴 열리기

void ClientManager::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->clientTreeView->mapToGlobal(pos);
    menu->exec(globalPos);
}

//선택한 항목 속성 값 라인에디터에 표시
void ClientManager::on_clientTreeView_clicked(const QModelIndex &index)
{
    QString id = clientModel->data(index.siblingAtColumn(0)).toString();
    QString name = clientModel->data(index.siblingAtColumn(1)).toString();
    QString phoneNumber = clientModel->data(index.siblingAtColumn(2)).toString();
    QString address = clientModel->data(index.siblingAtColumn(3)).toString();
    QString email = clientModel->data(index.siblingAtColumn(4)).toString();

    ui->clientInputIDText->setText(id);
    ui->clientInputNameText->setText(name);
    ui->clientInputPHText->setText(phoneNumber);
    ui->clientInputAddressText->setText(address);
    ui->clientInputEmailText->setText(email);
}


void ClientManager::resetSearchResult()
{
    ui -> clientSearchText-> clear();
    clientModel->setFilter("iswithdrow = 0");
    clientModel->select();
    ui->clientTreeView->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
}


