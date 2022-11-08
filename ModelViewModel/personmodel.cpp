#include "personmodel.h"


PersonModel::PersonModel(QObject *parent) : QAbstractListModel(parent)
{
    persons.append(new Person("Jamie Lannister", "red", 33));
    persons.append(new Person("Marry Lane", "cyan", 26));
    persons.append(new Person("Steve Moors", "yellow", 44));
    persons.append(new Person("Victor Trunk", "dodgerblue", 30));
    persons.append(new Person("Ariel geeny", "blue", 33));
    persons.append(new Person("Knut Vikran", "lightblue", 26));
}

PersonModel::~PersonModel()
{

}
