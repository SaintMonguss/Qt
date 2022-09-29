#ifndef SCRATCHPAD_H
#define SCRATCHPAD_H

#include <QWidget>

class ScratchPad : public QWidget
{
    Q_OBJECT

public:
    explicit ScratchPad(QWidget *parent = nullptr);
    ~ScratchPad();


protected:

    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

    void mousePressEvent(QMouseEvent * event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent* event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent * event) Q_DECL_OVERRIDE;


private :
    void resizeImage(QImage *image, const QSize &newSize);

    bool modified;
    QImage image;
    QPointF prevPos;
    QColor paintColor;
    qreal paintSize;


public slots:
//    void saveImage();
    void setPaintColor();
    void setPaintSize(qreal);

};
#endif // SCRATCHPAD_H
