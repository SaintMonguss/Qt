#include "counter.h"

counter::counter(QObject *parent) : QObject{parent}
{

}

void counter::setValue(int value)
{
    if(value != m_value)
    {
        m_value = value;
        Q_EMIT valueChanged(value);
    }
}
