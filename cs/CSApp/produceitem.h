#ifndef PRODUCEITEM_H
#define PRODUCEITEM_H

#include <QTreeWidgetItem>

class ProduceItem : public QTreeWidgetItem
{
public:
    explicit ProduceItem(int id = 0, QString = "", int = 0, int = 0);

    QString getName() const;
    void setName(QString&);
    int getPrice() const;
    void setPrice(int&);
    int getQuantity() const;
    void setQuantity(int&);
    int id() const;
    bool operator==(const ProduceItem &other) const;
};

#endif // PRODUCEITEM_H
