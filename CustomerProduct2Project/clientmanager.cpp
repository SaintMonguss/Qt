#include <iostream>
#include <QString>
#include <iomanip>
#include <stdio.h>
#include <QDebug>
#include <QFile>
#include <QMap>
#include <QMessageBox>
#include <QMenu>
#include <QPixmap>

#include "Client.h"
#include "clientmanager.h"
#include "ui_clientmanager.h"

ClientManager::ClientManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientManager)
{

    ui->setupUi(this);

    QAction* removeAction = new QAction(tr("&Remove"));
    connect(removeAction, SIGNAL(triggered()), SLOT(DelObj()));

    menu = new QMenu;
    menu->addAction(removeAction);
    ui->clientTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui-> clientTreeWidget, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
    connect(ui -> clientSearchButton, SIGNAL(clicked()), SLOT(SearchObj()));
    connect(ui -> clientModifyButton, SIGNAL(clicked()), this, SLOT(ModiObj()));
    connect(ui-> clientInputConfirmButton, SIGNAL(clicked()), SLOT(AddObj()));
    connect(ui -> clientResetButton, SIGNAL(clicked()), SLOT(resetSearchResult()));

    QFile file("clientlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    idHistory = in.readLine().toInt(); // 아이디 히스토리 유지
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");
        if(row.size()) {
            int id = row[0].toInt();
            Client* c = new Client(id, row[1], row[2], row[3], row[4]);
            ui -> clientTreeWidget ->addTopLevelItem(c);
            clientList.insert(id, c);
            emit clientAdded(id, row[1]);
        }
    }
    file.close( );
}

ClientManager::~ClientManager()
{
    delete ui;

    //파일 저장
    QFile file("clientlist.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << idHistory << "\n";
    for (const auto& v : clientList) {
        Client* c = v;
        out << QString::number(c->GetId()) << ", ";
        out << c->GetName() << ", ";
        out << c->GetPhoneNumber() << ", ";
        out << c->GetAddress() << ", ";
        out << c->GetEmail() << "\n";
    }
    file.close( );
}


//고객 정보 추가
void ClientManager::AddObj()
{
    Client* client;
    int id;

    if(ui -> clientInputIDText->text() != "")
    {
        QMessageBox::information(this, "ID 입력 금지", "신규 고객 등록시에는 ID 입력 금지");
        return;
    }

    if (clientList.empty())
    {
        idHistory  = id = 1;
    }
    else
    {
        id = idHistory + 1;
        idHistory += 1;
    }
    if(
            ui -> clientInputNameText->text() != "" &&
            ui -> clientInputPHText->text() != "" &&
            ui -> clientInputAddressText->text() != "" &&
            ui -> clientInputEmailText->text() != "")
    {
        client = new Client(id);
        client->SetName(ui -> clientInputNameText->text());
        client->SetPhoneNumber(ui -> clientInputPHText -> text());
        client->SetAddress(ui -> clientInputAddressText -> text());
        client->SetEmail(ui -> clientInputEmailText -> text());
        clientList.insert(id, client );
        ui -> clientTreeWidget ->addTopLevelItem(client);
        ui -> clientTreeWidget -> update();
        emit clientAdded(id, ui -> clientInputNameText->text());
        return;
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
    QTreeWidgetItem* item = ui->clientTreeWidget->currentItem();
    if(item != nullptr) {
        clientList.remove(item->text(0).toInt());
        ui->clientTreeWidget->takeTopLevelItem(ui->clientTreeWidget->indexOfTopLevelItem(item));
//        delete item;
        ui->clientTreeWidget->update();
        return;
    }
}

// 고객 정보 수정
void ClientManager::ModiObj()
{
    int id;
    Client* client;
    if(
            ui -> clientInputIDText->text() != "" &&
            ui -> clientInputNameText->text() != "" &&
            ui -> clientInputPHText->text() != "" &&
            ui -> clientInputAddressText->text() != "" &&
            ui -> clientInputEmailText->text() != "")
    {
        id = (ui -> clientInputIDText->text()).toInt();
        if(clientList.find(id) == clientList.end())
        {
            QMessageBox::information(this, "안내", "해당 하는 ID의 고객 정보가 없습니다.");
            return;
        }

        client = clientList.find(id).value();			// 찾아서 클라이언트 객체를 할당
        client->SetName(ui -> clientInputNameText->text());
        client->SetPhoneNumber(ui -> clientInputPHText->text());
        client->SetAddress(ui -> clientInputAddressText->text());
        client->SetEmail(ui -> clientInputEmailText->text());
        return;
    }
    else
        QMessageBox::information(this, "안내", "수정 하고자 하는 고객의 모든 정보를 입력해 주세요.");
    return;

}

// 고객 정보 검색
void ClientManager::SearchObj()
{
    QString target = ui-> clientComboBox->currentText();
    if (target == "tr(\"ID\")")
        for (auto itr = clientList.begin(); itr != clientList.end(); itr++)
        {
            if (itr.value()->GetId() == ui->clientSearchIDText->text().toInt())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == "tr(\"name\")")
        for (auto itr = clientList.begin(); itr != clientList.end(); itr++)
        {
            if (itr.value()->GetName() == ui->clientSearchNameText->text())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == "tr(\"phoneNumber\")")
        for (auto itr = clientList.begin(); itr != clientList.end(); itr++)
        {
            if (itr.value()->GetPhoneNumber() == ui->clientSearchPHText -> text())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == "tr(\"address\")")
        for (auto itr = clientList.begin(); itr != clientList.end(); itr++)
        {
            if (itr.value()->GetAddress() == ui -> clientSearchAddressText -> text())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == "tr(\"E-mail\")")
        for (auto itr = clientList.begin(); itr != clientList.end(); itr++)
        {
            if (itr.value()->GetEmail() == ui -> clientSearchEmailText ->text())
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    return;
}



//고객 한명의 정보를 리턴하는 함수
Client* ClientManager::TossObj(int id)
{
    Client* client =nullptr;
    if(clientList.find(id) == clientList.end())
    {
        qDebug() << "해당하는 ID 없음";
        return client;
    }
    client = clientList.find(id).value();
    return client;
}
//선택시 메뉴 열리기

void ClientManager::showContextMenu(const QPoint &pos)
{
    QPoint globalPos = ui->clientTreeWidget->mapToGlobal(pos);
    menu->exec(globalPos);
}

//선택한 항목 속성 값 라인에디터에 표시
void ClientManager::on_clientTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    Q_UNUSED(column);
    ui->clientInputIDText->setText(item->text(0));
    ui->clientInputNameText->setText(item->text(1));
    ui->clientInputPHText->setText(item->text(2));
    ui->clientInputAddressText->setText(item->text(3));
    ui->clientInputEmailText->setText(item->text(4));
}

void ClientManager::resetSearchResult()
{
    ui -> clientSearchIDText-> clear();
    ui -> clientSearchNameText -> clear();
    ui -> clientSearchPHText -> clear();
    ui -> clientSearchAddressText -> clear();
    ui -> clientSearchEmailText -> clear();
    for (auto itr = clientList.begin(); itr != clientList.end(); itr++)
    {
        itr.value()->setHidden(false);
    }
}
