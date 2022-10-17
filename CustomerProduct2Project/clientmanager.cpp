#include <iostream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <windows.h>
#include <QDebug>
#include <QFile>


#include "Client.h"
#include "clientmanager.h"
#include "ui_clientmanager.h"

ClientManager::ClientManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientManager)
{
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
            //ui->treeWidget->addTopLevelItem(c);
            clientList.insert(id, c);
        }
    }
    file.close( );

    ui->setupUi(this);
}

ClientManager::~ClientManager()
{
    //파일 저장
    QFile file("clientlist.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    for (const auto& v : clientList) {
        Client* c = v;
        out << c->GetId() << ", " << c->GetName() << ", ";
        out << c->GetPhoneNumber() << ", ";
        out << c->GetAddress() << ", ";
        out << c->GetEmail() << "\n";
    }
    file.close( );
    delete ui;
}


//고객 정보 추가
void ClientManager::AddObj(QString name, QString phoneNumber, QString address, QString e_mail)
{
    Client* client;
    int id;

    if (clientList.empty())
        id = 1;
    else
        id = (clientList.lastKey()) + 1; // lastkey 작동 방식 확인 필요
    try
    {
        client = new Client(id);
    }
    catch (const std::bad_alloc& e)
    {
        std::cout << "메모리 할당 실패";
        return;
    }

    client->SetName(name);
    client->SetPhoneNumber(phoneNumber);
    client->SetAddress(address);
    client->SetEmail(e_mail);
    try
    {
        if (clientList.find(id) == clientList.end())
            throw;
        clientList.insert(id, client );
    }
    catch (...)
    {
        qDebug() <<"키 ID 중복 발생";
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
void ClientManager::SerchObj()
{
    string name;
    map<int, Client*> serchList;

    system("cls");

    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
    std::cout << "                                                        고객 정보 검색" << std::endl;
    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
    std::cout << std::endl;

    std::cout << "검색할 대상의 이름을 입력해 주세요 : ";
    std::cin >> name;

    for (auto itr = clientList.begin(); itr != clientList.end(); itr++)
    {
        if (name == itr->second->GetName())
            serchList[itr->first] = itr->second;
    }
    if (serchList.empty())
    {
        std::cout << "[" << name << "]" << " 의 검색 결과가 없습니다...";
        Sleep(1500);
        return;
    }
    system("cls");
    printClientForm(serchList);
    std::cout << std::endl;
    std::cout << "[" << name << "]" << " 검색 결과" << std::endl;
    std::cout << std::endl;
    std::cout << "이전 화면으로 돌아가려면 enter를 입력해 주세요...";
    while (getchar() != '\n');
    getchar(); // 제어 흐름 정지
    return;

}

//고객 한명의 정보를 리턴하는 함수 / 반환값 any 형
void* ClientManager::TossObj(int id)
{
    Client* client =nullptr;
    try
    {
        client = clientList.at(id);
    }
    catch (std::out_of_range e)
    {
        std::cout << "해당하는 ID는 존재하지 않습니다!!" << std::endl;
        Sleep(1000);
    }

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
