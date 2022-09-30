#ifndef IMAGESLIDE_H
#define IMAGESLIDE_H

#include <QQuickWidget>

class QQuickWidget;

class ImageSlide : public QQuickWidget
{
    Q_OBJECT

public:
    explicit ImageSlide(QWidget *parent = 0);

public slots:
    void reloadImages();
    void selectItem(const QString &msg);

protected:
//    void resizeEvent(QResizeEvent *) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;

signals:
    void itemSelected(QString);
};

#endif // IMAGESLIDE_H
