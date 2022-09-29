#include "clientitem.h"

#include <QLabel>
#include <iostream>

using namespace std;

ClientItem::ClientItem(int id, string name, string phoneNumber, string address)
    : m_id(id), m_name(name), m_phoneNumber(phoneNumber), m_address(address)
{
    setText(0, QString::number(id));
    setText(1, name.c_str());
    setText(2, phoneNumber.c_str());
    setText(3, address.c_str());
}

string ClientItem::getName() const
{
    return m_name;
}

void ClientItem::setName(string& name)
{
    m_name = name;
    setText(1, name.c_str());
}

string ClientItem::getPhoneNumber() const
{
    return m_phoneNumber;
}

void ClientItem::setPhoneNumber(string& phoneNumber)
{
    m_phoneNumber = phoneNumber;
    setText(2, phoneNumber.c_str());
        // c_str() --> const char*
}

string ClientItem::getAddress() const
{
    return m_address;
}

void ClientItem::setAddress(string& address)
{
    m_address = address;
    setText(3, address.c_str());
}

int ClientItem::id() const
{
    return m_id;
}

// Define copy assignment operator.
bool ClientItem::operator==(const ClientItem &other) const {
    return (this->m_name == other.m_name);
}
