#include "mainwindow.h"
#include "pendulumcontroller.h"
#include "pendulumitem.h"

#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsView* view = new QGraphicsView;
    QGraphicsScene* scene = new QGraphicsScene(view);
    view -> setScene(scene);

    PendulumItem *pendulum = new PendulumItem;
    scene -> addItem(pendulum);
    PendulumController controller(pendulum);
    view -> setRenderHint(QPainter::Antialiasing);

    view -> resize(320, 240);
    view -> show();

    return a.exec();
}
