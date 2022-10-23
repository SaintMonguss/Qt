#include "ordermanager.h"
#include "ui_ordermanager.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <windows.h>
#include <QFile>
#include <QMap>
#include <QMessageBox>

// 생성자 파일 불러오기
OrderManager::OrderManager(ClientManager* CM, ProductManager* PM) : CM(CM), PM(PM) ,
    ui(new Ui::OrderManager)
{
    ui->setupUi(this);

    QFile file("orderlist.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    idHistory = in.readLine().toInt(); // 아이디 히스토리 유지
    while (!in.atEnd()) {
        QString line = in.readLine();
        QList<QString> row = line.split(", ");
        if (row.size()) {
            int id = row[0].toInt();
            QString productName = row[1];
            QString clientName = row[2];
            int date = row[3].toInt();
            int clientId = row[4].toInt();
            int orderPrice = row[5].toInt();
            int orderStock = row[6].toInt();
            Order* c = new Order(id, productName, clientName, date, clientId, orderPrice, orderStock);
            orderList.insert( id, c );
        }
    }
    file.close();
};

//소멸자 파일 저장
OrderManager::~OrderManager()
{
    delete ui;

    //파일 저장
    QFile file("orderlist.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    out << idHistory << "\n";
        for (const auto& v : orderList) {
            Order* c = v;
            out << QString::number(c -> GetOrderId()) << ", ";
            out << c -> GetProductName() << ", ";
            out << c -> GetClientName() << ", ";
            out << QString::number(c -> GetDate()) << ", ";
            out << QString::number(c->GetClientId()) << ", ";
            out << QString::number(c->GetOrderPrice()) << ", ";
            out << QString::number(c->GetOrderStock()) << "\n";
        }
    file.close();
}



//주문 정보 추가
void OrderManager::AddObj()
{
    Order* order;
    int id;

    if(ui -> orderInputIdText->text() != "")
    {
        QMessageBox::information(this, "ID 입력 금지", "신규 주문 등록시에는 ID 입력 금지");
        return;
    }

    if (orderList.empty())
    {
        idHistory  = id = 1;
    }
    else
    {
        id = idHistory + 1;
        idHistory += 1;
    }
    if(
            ui -> orderInputClientIdText->text() != "" &&
            ui -> orderInputProductNameText->text() != "" &&
            ui -> orderInputDateText->text() != "" &&
            ui -> orderInputOrderStockText->text() != "")
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

    ui -> clientInputNameText-> clear();
    ui -> clientInputPHText -> clear();
    ui -> clientInputAddressText -> clear();
    ui -> clientInputEmailText -> clear();

    return;
}

// 주문 정보 삭제
void OrderManager::DelObj()
{
    int id;
    char check;
    Order *order;

    system("cls");
    printOrderForm(orderList);
    std::cout << std::endl;;
    std::cout << std::endl;;
    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
    std::cout << "                                                          주문 이력 삭제" << std::endl;
    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────" << std::endl;

    std::cout << std::endl;
    std::cout << "뒤로 가고 싶다면 -1 입력" << std::endl << std::endl;
    std::cout << "삭제할 주문의 ID를 입력 해주세요 : ";
    id = InputFormat::IntCin();
    if (id == -1)
        return;
    try
    {
        orderList.at(id);
    }
    catch (std::out_of_range e)
    {
        std::cout << "해당하는 주문 ID는 존재하지 않습니다!!" << std::endl;
        Sleep(1000);
        return;
    }
    order = orderList.find(id)->second;					// 찾아서 클라이언트 객체를 할당
    std::cout << "[" << order->GetOrderId() << "]" << " 번 주문 이력을 삭제 하시겠습니까?" << std::endl;
    do
    {
        cin.ignore(999, '\n');							//버퍼 청소
        std::cout << "[ Y / N ] : ";
        std::cin >> check;
        check = toupper(check);							// 대문자 전환
    } while ((check != 'Y') && (check != 'N'));
    if (check == 'N')
        return;
    orderList.erase(id);
    std::cout << "[" << order->GetOrderId() << "]" << " 번 주문 이력을 삭제했습니다" << std::endl;
    Sleep(1500);
    system("cls");
}


// 주문 이력 수정
void OrderManager::ModiObj()
{
    int id;
    int num;
    Date date;
    Order* order;
    string tmp;

    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
    std::cout << "                                                       주문 이력 수정" << std::endl;
    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
    std::cout << std::endl;
    std::cout << "수정할 수 있는 항목은 주문 수량과 날짜입니다.";
    std::cout << std::endl;
    std::cout << "뒤로 가고 싶다면 -1 입력" << std::endl << std::endl;
    std::cout << "수정할 주문의 ID를 입력 해주세요 : ";
    id = InputFormat::IntCin();
    if (id == -1)
        return;
    try
    {
        orderList.at(id);
    }
    catch (std::out_of_range e)
    {
        std::cout << "해당하는 ID는 존재하지 않습니다!!" << std::endl;
        Sleep(1000);
        return;
    }
    order = orderList.find(id)->second;					// 찾아서 클라이언트 객체를 할당
    std::cout << "현재 수량 : [ " << order->GetOrderStock() << " ]" << std::endl;
    std::cout << "수정할 수량 : ";
    num = InputFormat::IntCin();
    order->SetOrderStock(num);
    std::cout << "현재 날짜 : [ "
        << order->GetDate().GetYear()<< "년 "
        << order->GetDate().GetMonth() << "월 "
        << order->GetDate().GetDay() << "일"
        << "]" << std::endl;
    do
    {
        std::cout << "수정할 날자 [년] (yyyy) : ";
        num = InputFormat::IntCin();
    } while (!date.SetYear(num));
    do
    {
        std::cout << "주문 날자 [월] (mm): ";
        num = InputFormat::IntCin();
    } while (!date.SetMonth(num));
    do
    {
        std::cout << "주문 날자 [일] (dd): ";
        num = InputFormat::IntCin();
    } while (!date.SetDay(num));
    order->SetDate(date);

    std::cout << "주문 정보 수정 완료";
    Sleep(1500);
    system("cls");
}

// 주문 정보 검색
void OrderManager::SerchObj()
{
    int id;
    map<int, Order*> serchList;

    system("cls");

    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
    std::cout << "                                                          주문 이력 검색" << std::endl;
    std::cout << "────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────" << std::endl;
    std::cout << std::endl;
    std::cout << "뒤로 가고 싶다면 -1 입력" << std::endl << std::endl;
    std::cout << "검색할 이력의 구매자 ID를 입력해 주세요 : ";
    id = InputFormat::IntCin();
    if (id == -1)
        return;
    for (auto itr = orderList.begin(); itr != orderList.end(); itr++)
    {
        if (id == itr->second->GetClientId())
            serchList[itr->first] = itr->second;
    }
    if (serchList.empty())
    {
        std::cout << "[" << id << "]" << " 고객의 주문 이력이 없습니다...";
        Sleep(1500);
        return;
    }
    system("cls");
    printOrderForm(serchList);
    std::cout << std::endl;
    std::cout << "[" << id << "]" << " 주문 이력 검색 결과" << std::endl;
    std::cout << std::endl;
    std::cout << "이전 화면으로 돌아가려면 enter를 입력해 주세요...";
    while (getchar() != '\n');
    getchar();										// 제어 흐름 정지
    return;

}

//주문 정보 조회
void OrderManager::PrintObj()
{
    system("cls");
    printOrderForm(orderList);
    std::cout << std::endl;
    std::cout << "이전 화면으로 돌아가려면 enter를 입력해 주세요...";
    while (getchar() != '\n');
    getchar();										// 제어 흐름 정지
    return;
}

void* OrderManager::TossObj(int id)
{
    Order* order = nullptr;
    try
    {
        order = orderList.at(id);
    }
    catch (std::out_of_range e)
    {
        std::cout << "해당하는 ID는 존재하지 않습니다!!" << std::endl;
        Sleep(1000);
    }
    return order;
}


// 고객 관련 출력 템플릿
void OrderManager::printOrderForm(map<int, Order*> &orderList) const
{
    Order* order;
    std::cout << "┌───────┬───────────────────┬──────────┬────────────────────────────────────────────┬────────┬──────────────────┬──────────────┐" << std::endl;;
    std::cout << "│   ID          주문일        구매자 ID                      상품 이름                상품 ID         가격            수량     │" << std::endl;;
    for (auto itr = orderList.begin(); itr != orderList.end(); itr++)
    {
        order = itr->second;
        std::cout << "├───────┼───────────────────┼──────────┼────────────────────────────────────────────┼────────┼──────────────────┼──────────────┤" << std::endl;;
        std::cout << "│ ";
        ///////////////////// ID 칸 양식
        cout.fill('0');
        std::cout.width(O_ID_WIDTH);
        std::cout << itr->first;
        cout.fill(' ');								// 공간 채움을 공백으로 다시 변경
        std::cout << " ";
        ///////////////////// 날짜 양식
        std::cout << "   ";
        std::cout << order->GetDate().GetYear() << "년 ";
        std::cout.width(2);
        std::cout << order->GetDate().GetMonth();
        std::cout << "월 ";
        std::cout.width(2);
        std::cout << order->GetDate().GetDay();
        std::cout << "일";
        std::cout << "  ";
        ///////////////////// 구매자 아이디 양식
        std::cout << "  ";
        std::cout.width(O_CLIENTID_WIDTH);
        cout.fill('0');
        std::cout << order->GetClientId();
        cout.fill(' ');								// 공간 채움을 공백으로 다시 변경
        std::cout << "  ";
        ///////////////////// 제품 명 양식
        std::cout << "  ";
        std::cout.width(O_PRODUCTNAME_WIDTH);
        std::cout << order->GetProductName();
        std::cout << " ";
        ///////////////////// 제품 ID 양식
        std::cout << "  ";
        cout.fill('0');
        std::cout.width(O_PRODUCTID_WIDTH);
        std::cout << order->GetProductId();
        cout.fill(' ');								// 공간 채움을 공백으로 다시 변경
        std::cout << " ";
        ///////////////////// 가격 양식
        std::cout << "  ";
        std::cout.width(O_PRICE_WIDTH);
        std::cout << order->GetOrderPrice();
        std::cout << " ";
        ///////////////////// 수량 양식
        std::cout.width(O_STOCK_WIDTH);
        std::cout << order->GetOrderStock();
        std::cout << " │" << std::endl;
    }
    std::cout << "└───────┴───────────────────┴──────────┴────────────────────────────────────────────┴────────┴──────────────────┴──────────────┘" << std::endl;;
    return;
}

std::vector<string> OrderManager::parseCSV(std::istream& file, char delimiter)
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
