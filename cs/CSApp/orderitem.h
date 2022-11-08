#ifndef ORDERITEM_H
#define ORDERITEM_H

#include <QTreeWidgetItem>

class OrderItem : public QTreeWidgetItem
{
public:
    explicit OrderItem(int id = 0, int = 0, QString = "",
                       int = 0, QString = "",
                       int = 0, int = 0, int = 0);

    int getCid() const;
    void setCid(int&);
    int getPid() const;
    void setPid(int&);
    int getPrice() const;
    void setPrice(int&);
    int getQuantity() const;
    void setQuantity(int&);
    int getTotalPrice() const;
    void setTotalPrice(int&);
    int id() const;
    bool operator==(const OrderItem &other) const;

private:
    int cid, pid;
};

#endif // ORDERITEM_H
