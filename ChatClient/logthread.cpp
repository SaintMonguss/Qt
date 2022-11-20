#include "logthread.h"

#include <QTreeWidgetItem>
#include <QFile>
#include <QDateTime>
#include <QMessageBox>

LogThread::LogThread(QObject *parent)
    : QThread{parent}
{
    QString format = "yyyyMMdd_hhmmss";
    filename = QString("log_%1.txt").arg(QDateTime::currentDateTime().toString(format));
}

void LogThread::saveData(QTextEdit* message)
{
    QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QByteArray log;

        log.append(message->toPlainText().toStdString());
        file.write(log);
        file.close( );
}
