#include "scratchpad.h"
#include <QtWidgets>

#define RADIUS 5

ScratchPad::ScratchPad(QWidget *parent)
    : QWidget(parent),paintSize(1), modified(false)
{
    setAttribute(Qt::WA_AcceptTouchEvents);
    setAttribute(Qt::WA_StaticContents);
    paintColor = Qt::black;
}

ScratchPad::~ScratchPad()
{
}

void ScratchPad::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    const QRect rect = event -> rect();
    painter.drawImage(rect.topLeft(), image, rect);
}

void ScratchPad::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height())
    {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}

void ScratchPad::resizeImage(QImage *image, const QSize &newSize)
{
    if (image -> size() == newSize)
        return;
    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255,255,255));
    QPainter painter (&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void ScratchPad::mousePressEvent(QMouseEvent* event)
{
    prevPos = event -> pos();
    QPen pen(paintColor, paintSize);
    pen.setCapStyle(Qt::RoundCap);
    QPainter painter(&image);
    painter.setPen(pen);
    painter.drawPoint(prevPos);
    painter.end();
    modified = true;
}

void ScratchPad::mouseMoveEvent(QMouseEvent* event)
{
    QPointF newPos = event -> pos();
    if(modified)
    {
        QPen pen(paintColor, paintSize);
        pen.setCapStyle(Qt::RoundCap);
        pen.setJoinStyle(Qt::RoundJoin);
        QPainter painter(&image);
        painter.setPen(pen);
        painter.drawLine(prevPos, newPos);
        painter.end();
    }
    int x1, x2, y1, y2;
    if(prevPos.x() < newPos.x())
    {
        x1 = prevPos.x();
        x2 = newPos.x();
    }
    else
    {
        x1 = newPos.x();
        x2 = prevPos.x();
    }

    if(prevPos.y() < newPos.y())
    {
        y1 = prevPos.y();
        y2 = newPos.y();
    }
    else
    {
        y1 = newPos.y();
        y2 = prevPos.y();
    }

    QRectF rect(x1, y1, x2 ,y2);
    update(rect.toRect().adjusted(-RADIUS, -RADIUS, +RADIUS, +RADIUS));
    prevPos = newPos;
}

void ScratchPad::mouseReleaseEvent(QMouseEvent* event)
{
    QPen pen(paintColor, paintSize);
    pen.setCapStyle(Qt::RoundCap);
    QPainter painter(&image);
    painter.setPen(pen);
    painter.drawPoint(prevPos);
    painter.end();
    modified = false;
    update();
}

