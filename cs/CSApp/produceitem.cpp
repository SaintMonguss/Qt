#include "produceitem.h"

ProduceItem::ProduceItem(int id, QString name, int price, int quantity)
{
    setText(0, QString::number(id));
    setText(1, name);
    setText(2, QString::number(price));
    setText(3, QString::number(quantity));
}

QString ProduceItem::getName() const
{
    return text(1);
}

void ProduceItem::setName(QString& name)
{
    setText(1, name);
}

int ProduceItem::getPrice() const
{
    return text(2).toInt();
}

void ProduceItem::setPrice(int& price)
{
    setText(2, QString::number(price));
}

int ProduceItem::getQuantity() const
{
    return text(3).toInt();
}

void ProduceItem::setQuantity(int& quantity)
{
    setText(3, QString::number(quantity));
}

int ProduceItem::id() const
{
    return text(0).toInt();
}

// Define copy assignment operator.
bool ProduceItem::operator==(const ProduceItem &other) const {
    return (this->text(1) == other.text(1));
}
