#include "debugerhandler.h"

#include <QApplication>
#include <stdio.h>
#include <stdlib.h>

void myDebugMsg(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    switch(type)
    {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s\n", qPrintable(msg));
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s\n", qPrintable(msg));
        break;
    case QtFatalMsg:
        fprintf(stderr, "Warning: %s\n", qPrintable(msg));
        abort();
    }
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myDebugMsg);
    QApplication a(argc, argv);

    qDebug("디버그");
    qWarning("_");
    qFatal("심각");

    return a.exec();
}
