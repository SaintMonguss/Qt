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
void ClientManager::AddObj(int Id, QString name, QString)
{
    string input;
    Client* client;
    int id;

    if (clientList.empty())
        id = 1;
    else
        id = (clientList.rbegin()->first) + 1;
    try
    {
        client = new Client(id);
    }
    catch (const std::bad_alloc& e)
    {
        std::cout << "메모리 할당 실패";
        return;
    }

    client->SetName(input);
    client->SetPhoneNumber(input);
    client->SetAddress(input);
    client->SetEmail(input);
    try
    {
        auto tmp = (clientList.insert({ id, client }));
        if (tmp.second == false)
            throw;
    }
    catch (...)
    {
        qDebug() <<"키 ID 중복 발생";
        return;
    }
    return;
}

// 고객 정보 삭제
void ClientManager::DelObj()
{
    int id;
    char check;
    Client *client;

    system("cls");
    printClientForm(clientList);
    std::cout << std::endl;;
    std::cout << std::endl;;
    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
    std::cout << "                                                         고객 정보 삭제" << std::endl;
    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
    std::cout << std::endl;
    std::cout << "뒤로 가고 싶다면 -1 입력" << std::endl << std::endl;
    std::cout << "삭제할 고객의 ID를 입력 해주세요 : ";
    id = InputFormat::IntCin();
    if (id == -1)
        return;
    try
    {
        clientList.at(id);
    }
    catch (std::out_of_range e)
    {
        std::cout << "해당하는 ID는 존재하지 않습니다!!" << std::endl;
        Sleep(1000);
        return;
    }
    client = clientList.find(id)->second;			// 찾아서 클라이언트 객체를 할당
    std::cout << client->GetName() << " 고객 정보를 삭제 하시겠습니까?"<<std::endl;
    do
    {
        cin.ignore(999, '\n');						//버퍼 청소
        std::cout << "[ Y / N ] : ";
        std::cin >> check;
        check = toupper(check);						// 대문자 전환
    } while ((check != 'Y') && (check != 'N'));
    if (check == 'N')
        return;
    clientList.erase(id);
    std::cout << "[" << client->GetName() << "]" << " 고객 정보를 삭제했습니다" << std::endl;
    Sleep(1500);
    system("cls");
}
// 고객 정보 수정
void ClientManager::ModiObj()
{
    int id;
    Client* client;
    string tmp;

    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
    std::cout << "                                                            고객 정보 수정" << std::endl;
    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
    std::cout << std::endl;
    std::cout << "뒤로 가고 싶다면 -1 입력" << std::endl << std::endl;
    std::cout << "수정할 고객의 ID를 입력 해주세요 : ";
    id = InputFormat::IntCin();
    if (id == -1)
        return;
    try
    {
        clientList.at(id);
    }
    catch (std::out_of_range e)
    {
        std::cout << "해당하는 ID는 존재하지 않습니다!!" << std::endl;
        Sleep(1000);
        return;
    }
    client = clientList.find(id)->second;			// 찾아서 클라이언트 객체를 할당
    std::cout << "현재 이름 : [ " << client->GetName() << " ]" << std::endl;
    std::cout << "수정할 이름 : ";
    std::cin >> tmp;
    client->SetName(tmp);
    std::cout << "현재 번호 : [ " << client->GetPhoneNumber() << " ]" << std::endl;
    std::cout << "수정할 번호 : ";
    std::cin >> tmp;
    client->SetPhoneNumber(tmp);
    std::cout << "현재 주소 : [ " << client->GetAddress() << " ]" << std::endl;
    std::cout << "수정할 주소 : ";
    std::cin.clear();
    cin.ignore(999, '\n');							//버퍼 청소 필요
    std::getline(std::cin, tmp, '\n');				// 한줄 전체를 받아야 함으로 getline() 사용
    client->SetAddress(tmp);
    std::cout << "현재 E-mail : [ " << client->GetEmail() << " ]" << std::endl;
    std::cout << "수정할 E-mail : ";
    std::cin >> tmp;
    client->SetEmail(tmp);
    std::cout << std::endl;
    std::cout << "고객 정보 수정 완료";
    Sleep(1500);
    system("cls");
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

//고객 정보 조회
void ClientManager::PrintObj()
{
    system("cls");
    printClientForm(clientList);
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

// 고객 관련 출력 템플릿
void ClientManager::printClientForm(map<int, Client*> &clientList) const
{
    Client* client;
    std::cout << "┌───────┬───────────┬──────────────┬────────────────────────────────────────────────────────────────┬─────────────────────────┐" << std::endl;;
    std::cout << "│   ID       이름          번호                                      주소                                       E-mail        │" << std::endl;;
    for (auto itr = clientList.begin(); itr != clientList.end(); itr++)
    {
        client = itr->second;
        std::cout << "├───────┼───────────┼──────────────┼────────────────────────────────────────────────────────────────┼─────────────────────────┤" << std::endl;;
        std::cout << "│ ";
        ///////////////////// ID 칸 양식
        cout.fill('0');
        std::cout.width(C_ID_WIDTH);
        std::cout << itr->first;
        cout.fill(' ');								// 공간 채움을 공백으로 다시 변경
        std::cout << " ";
        ///////////////////// 이름 칸 양식
        std::cout << "  ";
        std::cout.width(C_NAME_WIDTH);
        std::cout << client->GetName();
        std::cout << "  ";
        ///////////////////// 번호 칸 양식
        std::cout << "  ";
        std::cout.width(C_PHONNUMBER_WIDTH);
        std::cout << client->GetPhoneNumber();
        std::cout << "  ";
        ///////////////////// 주소 칸 양식
        std::cout.width(C_ADRESS_WIDTH);
        std::cout << client->GetAddress();
        std::cout << "  ";
        ///////////////////// 이메일 칸 양식
        std::cout.width(C_EMAIL_WIDTH);
        std::cout << client->GetEmail();
        std::cout << " │" << std::endl;
    }
    std::cout << "└───────┴───────────┴──────────────┴────────────────────────────────────────────────────────────────┴─────────────────────────┘" << std::endl;;
    return;
}

std::vector<string> ClientManager::parseCSV(std::istream& file, char delimiter)
{
    std::stringstream ss;
    std::vector<string> row;
    string t = " \n\r\t";

    while (!file.eof()) {
        char c = file.get();
        if (c == delimiter || c == '\r' || c == '\n') {
            if (file.peek() == '\n') file.get();
            string s = ss.str();
            s.erase(0, s.find_first_not_of(t));
            s.erase(s.find_last_not_of(t) + 1);
            row.push_back(s);
            ss.str("");
            if (c != delimiter) break;
        }
        else {
            ss << c;
        }
    }
    return row;
}
