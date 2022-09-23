#include "application.h"
#include "qteditor.h"

#include <QDebug>

Application::Application(int& argc, char** argv) : QApplication(argc, argv)
{
}

bool Application::notify(QObject* receiver, QEvent *e)
{
    qDebug() << " Application : notify called";

    if(e -> type() == QEvent::MouseButtonPress)
    {
        qDebug() << "Application : mouse event";
        return false;
    }
}
