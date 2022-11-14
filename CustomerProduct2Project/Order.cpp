//#include <iostream>
//#include <QString>

//#include "Order.h"

//Order::Order(const int id) : m_orderId(id)
//{
//    setText(0, QString::number(id));
//}
//Order::Order(const int id, int clientId, QString clientName, QString productName, int date,  int orderPrice, int orderStock) :
//    m_orderId(id), m_productName(productName), m_clientName(clientName), m_date(date), m_clientId(clientId),
//    m_orderPrice(orderPrice), m_orderStock(orderStock)
//{
//    setText(0, QString::number(id));
//    setText(1, QString::number(clientId));
//    setText(2, clientName);
//    setText(3, productName);
//    setText(4, QString::number(date));
//    setText(5, QString::number(orderPrice));
//    setText(6, QString::number(orderStock));
//}


//int Order::GetOrderId() const
//{
//    return m_orderId;
//}
//int Order::GetClientId() const
//{
//    return m_clientId;
//}
//int Order::GetOrderPrice() const
//{
//    return m_orderPrice;
//}
//int Order::GetOrderStock() const
//{
//    return m_orderStock;
//}
//int Order::GetDate() const
//{
//    return m_date;
//}
//QString Order::GetClientName() const
//{
//    return m_clientName;
//}

//QString Order::GetProductName() const
//{
//    return m_productName;
//}

//void Order::SetProductName(QString productName)
//{
//    m_productName = productName;
//    setText(3, productName);
//}

//void Order::SetClientName(QString clientName)
//{
//    m_clientName = clientName;
//    setText(2, clientName);
//}

//void Order::SetDate(int date)
//{
//    m_date = date;
//    setText(4, QString::number(date));
//}

//void Order::SetClientId(int clientId)
//{
//    m_clientId = clientId;
//    setText(1, QString::number(clientId));
//}

//void Order::SetOrderPrice(int orderPrice)
//{
//    m_orderPrice = orderPrice;
//    setText(5, QString::number(orderPrice));
//}
//void Order::SetOrderStock(int orderStock)
//{
//    m_orderStock = orderStock;
//    setText(6, QString::number(orderStock));
//}


