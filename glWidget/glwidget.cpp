#include "glwidget.h"
#include <QPainter>

GLWidget::GLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    resize(200,160);
}

GLWidget::~GLWidget()
{
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3f(1.f, 0.f, 0.f);
        glVertex2f(0.0, 0.0);
        glColor3f(0.f,1.f,0.f);
        glVertex2f(width()/2, height());
        glColor3f(0.f, 0.f, 1.f);
        glVertex2f(width(), 0.0);
    glEnd();

    glFlush();

    QPainter painter (this);
    painter.setPen(Qt::white);
    painter.setFont(QFont("Helvetica", 30));
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.drawText(45.0, 120.0, QString("Hello Qt"));
    painter.end();
}

void GLWidget::resizeGL(int w, int h)
{
    qDebug("W : %d, H : %d\n, w , h");

    glViewport(0, 0, (GLint)w/2, (GLint)h/2);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
