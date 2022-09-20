#include "object.h"
#include <QCoreApplication>
#include <QDebug>
#include <QScopedPointer>

void moo(QScopedPointer<Object> &mypointer)
{
    qInfo()<< ">>> Do" << mypointer.data();
}

void use(Object *obj)
{
    if(!obj) return;
    qInfo() << " >>> use" << obj;
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    QObject *obj1 = new QObject(nullptr);
//    obj1 -> setObjectName("MyObject");

//    QPointer<QObject> p(obj1);

//    Object obj2;
//    obj2.widget = p;
//    obj2.useWidget();

//    delete obj1;
//    obj2.useWidget();



    return a.exec();
}
