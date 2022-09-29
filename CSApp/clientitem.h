#ifndef CLIENTITEM_H
#define CLIENTITEM_H

#include <iostream>

using namespace std;

#include <QTreeWidgetItem>

class QLabel;

class ClientItem : public QTreeWidgetItem
{
public:
    explicit ClientItem(int id = 0, string = "", string = "", string = "");

    string getName() const;
    void setName(string&);
    string getPhoneNumber() const;
    void setPhoneNumber(string&);
    string getAddress() const;
    void setAddress(string&);
    int id() const;
    bool operator==(const ClientItem &other) const;

private:
    int m_id;
    string m_name;
    string m_phoneNumber;
    string m_address;
};

#endif // CLIENTITEM_H
