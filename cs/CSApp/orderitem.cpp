#include "orderitem.h"

OrderItem::OrderItem(int id, int cid, QString cname,
                     int pid, QString pname,
                     int price, int quantity, int totalPrice)
    : cid(cid), pid(pid)
{
    setText(0, QString::number(id));
    setText(1, cname);
    setText(2, pname);
    setText(3, QString::number(price));
    setText(4, QString::number(quantity));
    setText(5, QString::number(totalPrice));
}

int OrderItem::getCid() const
{
    return cid;     // text(1).toInt();
}

void OrderItem::setCid(int& id)
{
    cid = id;
    setText(1, QString::number(id));
}

int OrderItem::getPid() const
{
    return pid;     // text(2).toInt();
}

void OrderItem::setPid(int& id)
{
    pid = id;
    setText(2, QString::number(id));
}

int OrderItem::getPrice() const
{
    return text(3).toInt();
}

void OrderItem::setPrice(int& price)
{
    setText(3, QString::number(price));
}

int OrderItem::getQuantity() const
{
    return text(4).toInt();
}

void OrderItem::setQuantity(int& quantity)
{
    setText(4, QString::number(quantity));
}

int OrderItem::getTotalPrice() const
{
    return text(5).toInt();
}

void OrderItem::setTotalPrice(int& quantity)
{
    setText(5, QString::number(quantity));
}

int OrderItem::id() const
{
    return text(0).toInt();
}

// Define copy assignment operator.
bool OrderItem::operator==(const OrderItem &other) const {
    return (this->text(1) == other.text(1));
}
