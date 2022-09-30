#include "pendulumcontroller.h"

PendulumController::PendulumController(QGraphicsItem* pendulum ,QObject *parent)
    : QObject{parent}, m_pendulum(pendulum)
{
    m_timeline.setFrameRange(-90, 90);
    m_timeline.setEasingCurve(QEasingCurve::InOutQuad);
    m_timeline.setDuration(100);
    m_timeline.setUpdateInterval(4);
    connect(&m_timeline, SIGNAL(frameChanged(int)), SLOT(slotRotateItem(int)));
    connect(&m_timeline, SIGNAL(finished()), this, SLOT(slotRestartTimeLine()), Qt::QueuedConnection);
    m_timeline.start();

}

void PendulumController::slotRotateItem(int r)
{
    m_pendulum -> resetTransform();
    m_pendulum -> setRotation(r);
}

void PendulumController::slotRestartTimeLine()
{
    m_timeline.toggleDirection();
    m_timeline.start();
}
