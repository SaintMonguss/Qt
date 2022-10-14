#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTcpServer>
#include <QTcpSocket>
#include <QLabel>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void clientConnect();
    void echoData();

private:
    QLabel *infoLabel;
    QTcpServer *tcpServer;
    QList<QTcpSocket *> clientList;
};
#endif // WIDGET_H
