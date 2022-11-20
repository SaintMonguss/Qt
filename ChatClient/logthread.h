#ifndef LOGTHREAD_H
#define LOGTHREAD_H

#include <QThread>
#include <QList>
#include <QTextEdit>

class QTreeWidgetItem;

class LogThread : public QThread
{
    Q_OBJECT
public:
    explicit LogThread(QObject *parent = nullptr);
    void saveData(QTextEdit*);

private:
    QString filename;

signals:
    void send(int data);
};


#endif // LOGTHREAD_H
