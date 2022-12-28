#include "widget.h"
#include <GL/glut.h>

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    xAngle = 25, yAngle = 25, zAngle =25;
    ex =ey =ez =0;

    setWindowTitle("OpenGL Viewing");
    resize(600, 600);
}

Widget::~Widget()
{
}

void Widget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void Widget::resizeGL(int w, int h)
{
    glViewport(0, 0, (GLint)w, (GLint)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(xAngle, 1.0f, 0.0f, 0.0f);
    glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
    glRotatef(zAngle, 0.0f, 0.0f, 1.0f);

    gluLookAt(
                ex, ey, ez,
                0.0, 0.0, -1.0,
                0.0, 1.0, 0.0);

    glPushMatrix();

    glColor3f(1,1,1);
    glBegin(GL_QUADS);
    glVertex2f(-0.5,0.5);
    glVertex2f(0.5,0.5);
    glVertex2f(0.5,-0.5);
    glVertex2f(-0.5,-0.5);
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1,1,1);
    glVertex3f(0.0, 0.0, -0.8);
    glColor3f(1,0,0);
    glVertex2f(0.5, 0.5);
    glVertex2f(-0.5, 0.5);

    glColor3f(1, 1, 0);
    glVertex2f(-0.5, -0.5);

    glColor3f(0,1,0);
    glVertex2f(0.5, 0.5);
    glEnd();

    glPopMatrix();
    glFlush();
}

void Widget::keyPressEvent(QKeyEvent* event)
{
    switch(event -> key()) {
    case Qt::Key_1:
        yAngle +=2;
        break;
    case Qt::Key_2:
        yAngle -=2;
        break;
    case Qt::Key_3:
        xAngle +=2;
        break;
    case Qt::Key_4:
        xAngle -=2;
        break;
    case Qt::Key_5:
        zAngle +=2;
    case Qt::Key_6:
        zAngle -=2;
        break;
    case Qt::Key_0:
        yAngle = xAngle = zAngle = 0.0;
        break;

    case Qt::Key_A:
        ex += 0.1;
        break;
    case Qt::Key_S:
        ex -= 0.1;
        break;
    case Qt::Key_D:
        ey += 0.1;
        break;
    case Qt::Key_F:
        ey -= 0.1;
        break;

    case Qt::Key_G:
        ez += 0.1;
        break;
    case Qt::Key_H:
        ez -= 0.1;
        break;
    case Qt::Key_J:
        ex =ey =ez = 0.0;
        break;
    }

    QString str = QString("ex : %1, ey: %2, ez: %3").arg(ex).arg(ey).arg(ez);
    setWindowTitle(str);

    update();
}
