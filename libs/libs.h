#ifndef LIBS_H
#define LIBS_H

#include "libs_global.h"

class LIBS_EXPORT Libs
{
public:
    Libs();

    void save(QStringList);
    QStringList load();
};

#endif // LIBS_H
