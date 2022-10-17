#ifndef __ORDER_H__
#define __ORDER_H__

#include <iostream>
#include <QString>

using std::cout;
using std::cin;
using std::string;


class Order
{
private:
	const int m_orderId;		// 주문의 식별 번호
    QString m_productName;
    QString m_clientName;
    int m_date;
    int m_clientId;// 구매자 식별 번호
	int m_orderPrice;
	int m_orderStock;
	

public:
	Order(const int );
    Order(const int, QString, QString, int, int, int, int);

	int GetOrderId() const;
	int GetClientId() const;
	int GetProductId() const;
	int GetOrderPrice() const;
	int GetOrderStock() const;
    int GetDate() const;
    QString GetProductName() const;



	void SetClientId(int);
	void SetProductId(int);
	void SetOrderPrice(int);
	void SetOrderStock(int);
    void SetDate(int);
    void SetProductName(QString);
};

#endif
