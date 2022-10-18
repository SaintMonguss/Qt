#include <iostream>
#include <QString>
#include <iomanip>
#include <stdio.h>
#include <windows.h>
#include <QDebug>
#include <QFile>
#include <QMap>


#include "Client.h"
#include "clientmanager.h"
#include "ui_clientmanager.h"

ClientManager::ClientManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientManager)
{
    ui->setupUi(this);

    connect(ui-> clientInputConfirmButton, SIGNAL(clicked()), SLOT(AddObj()));



    QFile file("clientlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");
        if(row.size()) {
            int id = row[0].toInt();
            Client* c = new Client(id, row[1], row[2], row[3], row[4]);
            ui -> clientTreeWidget ->addTopLevelItem(c);
            clientList.insert(id, c);
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

    if (clientList.empty())
    {
        id = 1;
    }
    else
    {
        id = (clientList.lastKey()) + 1; // lastkey 작동 방식 확인 필요
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
        return;
    }

    return;
}

// 고객 정보 삭제
void ClientManager::DelObj(int id)
{
    if(clientList.find(id) == clientList.end())
    {
        qDebug() << "해당하는 ID는 존재하지 않음";
        return;
    }
    clientList.remove(id);
}

// 고객 정보 수정
void ClientManager::ModiObj(int id ,QString name, QString phoneNumber, QString address, QString e_mail)
{
    Client* client;
    try
    {
        if(clientList.find(id) == clientList.end())
            throw;
    }
    catch (...)
    {
        qDebug() << "해당하는 ID 없음";
        return;
    }
    client = clientList.find(id).value();			// 찾아서 클라이언트 객체를 할당
    client->SetName(name);
    client->SetPhoneNumber(phoneNumber);
    client->SetAddress(address);
    client->SetEmail(e_mail);
    return;
}

// 고객 정보 검색
void ClientManager::SerchObj(int id)
{
    for (auto itr = clientList.begin(); itr != clientList.end(); itr++)
    {
        if (itr.key() != id)
            itr.value()->setHidden(true);
        else
            itr.value()->setHidden(false);
    }
    return;
}

void ClientManager::SerchObj(QString target, QString value)
{
    if (target == "tr(\"name\")")
        for (auto itr = clientList.begin(); itr != clientList.end(); itr++)
        {
            if (itr.value()->GetName() == value)
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == "tr(\"phoneNumber\")")
        for (auto itr = clientList.begin(); itr != clientList.end(); itr++)
        {
            if (itr.value()->GetPhoneNumber() == value)
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == "tr(\"address\")")
        for (auto itr = clientList.begin(); itr != clientList.end(); itr++)
        {
            if (itr.value()->GetAddress() == value)
                itr.value()->setHidden(false);
            else
                itr.value()->setHidden(true);
        }
    if (target == "tr(\"E-mail\")")
        for (auto itr = clientList.begin(); itr != clientList.end(); itr++)
        {
            if (itr.value()->GetEmail() == value)
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
    try
    {
        if(clientList.find(id) == clientList.end())
            throw;
    }
    catch (...)
    {
        qDebug() << "해당하는 ID 없음";
        return client;
    }
    client = clientList.find(id).value();
    return client;
}

//std::vector<QString> ClientManager::parseCSV(std::istream& file, char delimiter)
//{
//    std::stringstream ss;
//    std::vector<QString> row;
//    string t = " \n\r\t";

//    while (!file.eof()) {
//        char c = file.get();
//        if (c == delimiter || c == '\r' || c == '\n') {
//            if (file.peek() == '\n') file.get();
//            string s = ss.str();
//            s.erase(0, s.find_first_not_of(t));
//            s.erase(s.find_last_not_of(t) + 1);
//            row.push_back(s);
//            ss.str("");
//            if (c != delimiter) break;
//        }
//        else {
//            ss << c;
//        }
//    }
//    return row;
//}
