#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QtOpenGL>
#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = nullptr);
    ~GLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
};
#endif // GLWIDGET_H
