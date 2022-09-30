#include "dataelement.h"

DataElement::DataElement(QObject *parent) : QObject(parent)
{

}

DataElement::DataElement(const QString &path, const QString &name, QObject *parent)
    : QObject(parent), m_path(path), m_name(name)
{
}

QString DataElement::path() const
{
    return m_path;
}

void DataElement::setPath(const QString &path)
{
    if (path != m_path) {
        m_path = path;
        emit pathChanged();
    }
}

QString DataElement::name() const
{
    return m_name;
}

void DataElement::setName(const QString &name)
{
    if (name != m_name) {
        m_name = name;
        emit nameChanged();
    }
}
