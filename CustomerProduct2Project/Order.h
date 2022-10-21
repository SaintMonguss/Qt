#ifndef __ORDER_H__
#define __ORDER_H__

#include <iostream>
#include <QString>
#include <QTreeWidgetItem>

using std::cout;
using std::cin;
using std::string;


class Order : public QTreeWidgetItem
{
private:
    const int m_orderId;
    QString m_productName;
    QString m_clientName;
    int m_date;
    int m_clientId;
    int m_orderPrice;
    int m_orderStock;


public:
    Order(const int );
    Order(const int, QString, QString, int, int, int, int);

    int GetOrderId() const;
    int GetClientId() const;
    int GetOrderPrice() const;
    int GetOrderStock() const;
    int GetDate() const;
    QString GetClientName() const;
    QString GetProductName() const;



    void SetClientId(int);
    void SetDate(int);
    void SetOrderPrice(int);
    void SetOrderStock(int);
    void SetClientName(QString);
    void SetProductName(QString);
};

#endif
