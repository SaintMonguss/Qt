#include "ProjectHeader.h"

#include <iostream>
#include <QString>


Client::Client(int id)
	: m_id(id), m_name(""), m_phoneNumber(""), m_address(""), m_Email("") {}

Client:: Client(int id, QString name, QString phoneNumber, QString address, QString email)
	: m_id(id), m_name(name), m_phoneNumber(phoneNumber), m_address(address), m_Email(email) {}

int Client::GetId() const
{
	return m_id;
}


QString Client::GetName() const
{
	return m_name;
}

QString Client::GetPhoneNumber() const
{
	return m_phoneNumber;
}

QString Client::GetAddress() const
{
	return m_address;
}

QString Client::GetEmail() const
{
	return m_Email;
}

void Client::SetName(QString name)
{
	m_name = name;
}

void Client::SetPhoneNumber(QString phoneNumber)
{
	m_phoneNumber = phoneNumber;
}

void Client::SetAddress(QString address)
{
	m_address = address;
}

void Client::SetEmail(QString email)
{
	m_Email = email;
}
