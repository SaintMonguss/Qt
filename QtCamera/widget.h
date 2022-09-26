#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QCamera;
class QImageCapture;
class QMediaRecorder;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QCamera *camera;
    QImageCapture *imageCapture;
    QMediaRecorder *recorder;

public slots:
    void captureImage();
    void recordVideo();
};
#endif // WIDGET_H
