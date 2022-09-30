#ifndef ScratchPad_H
#define ScratchPad_H

#include <QWidget>

class ScratchPad : public QWidget
{
    Q_OBJECT

public:
    explicit ScratchPad(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent* event) Q_DECL_OVERRIDE;

private:
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified;
    QImage image;
    QPointF prevPos;
    QColor paintColor;
    qreal  paintSize;

public slots:
    void setPaintColor();
    void saveImage();
    void setPaintSize(qreal);
};

#endif // ScratchPad_H
