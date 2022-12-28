#ifndef LIBS_H
#define LIBS_H

#include <QStringList>

class  Libs
{
public:
    Libs();

    void save(QStringList);
    QStringList load();
};

#endif // LIBS_H
