#include <QMouseEvent>
#include <QScrollBar>
#include <QWheelEvent>
#include <QTimeLine>
#include <QPinchGesture>
#include <QGraphicsItem>

#include "imageview.h"

ImageView::ImageView(QWidget *parent)
    : QGraphicsView(parent)
{
    _pan = false;
    _currentStepScaleFactor = 1;
    resetTransform();
    grabGesture(Qt::PinchGesture);
    setAttribute(Qt::WA_AcceptTouchEvents);
}

void ImageView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        _pan = true;
        _panStartX = event->pos().x();
        _panStartY = event->pos().y();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
        return;
    }
    event->ignore();
}

void ImageView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        _pan = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }
    event->ignore();
}

void ImageView::mouseMoveEvent(QMouseEvent *event)
{
    if (_pan)  {
        horizontalScrollBar() ->setValue(horizontalScrollBar()->value() - (event->pos().x() - _panStartX));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->pos().y() - _panStartY));
        _panStartX = event->pos().x();
        _panStartY = event->pos().y();
        event->accept();
        return;
    }
    event->ignore();
}

void ImageView::wheelEvent(QWheelEvent *event)
{
    int numDegrees = event->angleDelta().y() / 8;
    int numSteps = numDegrees / 15; // see QWheelEvent documentation
    _numScheduledScalings += numSteps;
    if (_numScheduledScalings * numSteps < 0) // if user moved the wheel in another direction, we reset previously scheduled scalings
        _numScheduledScalings = numSteps;

    QTimeLine *anim = new QTimeLine(350, this);
    anim->setUpdateInterval(20);

    connect(anim, SIGNAL (valueChanged(qreal)), SLOT (scalingTime(qreal)));
    connect(anim, SIGNAL (finished()), SLOT (animFinished()));
    anim->start();
}

void ImageView::scalingTime(qreal x)
{
    Q_UNUSED(x);
    qreal factor = 1.0 + qreal(_numScheduledScalings) / 300.0;
    scale(factor, factor);
}

void ImageView::animFinished()
{
    (_numScheduledScalings > 0)?_numScheduledScalings--:_numScheduledScalings++;
//    delete sender();
        sender() -> deleteLater();
}

bool ImageView::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture)
        return gestureEvent(static_cast<QGestureEvent*>(event));
    return QGraphicsView::event(event);
}

bool ImageView::gestureEvent(QGestureEvent *event)
{
    qDebug("gestureEvent");
    if (QGesture *pinch = event->gesture(Qt::PinchGesture))
        pinchTriggered(static_cast<QPinchGesture *>(pinch));
    return true;
}

void ImageView::pinchTriggered(QPinchGesture *gesture)
{
    qDebug("pinchTriggered");
    QPinchGesture::ChangeFlags changeFlags = gesture->changeFlags();
    if (changeFlags & QPinchGesture::RotationAngleChanged) {
        qreal rotationDelta = gesture->rotationAngle() - gesture->lastRotationAngle();
        _rotationAngle += rotationDelta;
    }
    if (changeFlags & QPinchGesture::ScaleFactorChanged) {
        _currentStepScaleFactor = gesture->totalScaleFactor();
    }
    if (gesture->state() == Qt::GestureFinished) {
        _scaleFactor *= _currentStepScaleFactor;
        _currentStepScaleFactor = 1;
    }
    update();
}
