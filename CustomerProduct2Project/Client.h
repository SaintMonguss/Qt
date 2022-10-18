#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <iostream>
#include <QString>
#include <QTreeWidgetItem>

using std::cout;
using std::cin;
using std::string;



class Client : public QTreeWidgetItem
{
private:
    int m_id;
    QString m_name;
    QString m_phoneNumber;
    QString m_address;
    QString m_Email;

public:
    Client(const int id);
    Client(int ,QString, QString, QString, QString);
	
	int GetId() const;
    QString GetName() const;
    QString GetPhoneNumber() const;
    QString GetAddress() const;
    QString GetEmail() const;

    void SetName(QString );
    void SetPhoneNumber(QString );
    void SetAddress(QString );
    void SetEmail(QString );

    bool operator==(const Client &other) const;
};

#endif
