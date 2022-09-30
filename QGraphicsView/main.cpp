#include "widget.h"

#include <QApplication>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGraphicsScene *scene = new QGraphicsScene;
    QGraphicsRectItem *rect = scene -> addRect(-10, -10, 120, 50);
    rect -> setPen(QPen(Qt::red));
    rect -> setBrush(QBrush(Qt::yellow));
    QGraphicsItem *item = new QGraphicsTextItem("Hello World");
    scene -> addItem(item);
    QGraphicsView *view = new QGraphicsView(scene);
    view -> show();

    return a.exec();
}
