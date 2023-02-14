#include "glscene.h"

#include <QColor>

GLScene::GLScene(QWidget* parent):
    QOpenGLWidget{ parent }
{

}

void GLScene::initializeGL()
{
    QColor bgc(255, 255, 255);
    initializeOpenGLFunctions();
    glClearColor(bgc.redF(), bgc.greenF(), bgc.blueF(), bgc.alphaF());
}

void GLScene::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLScene::paintGL()
{
    QColor colors[10] = {
        QColor("cyan"), QColor("magenta"), QColor("darkGreen"),
        QColor("darkRed"), QColor("darkCyan"), QColor("darkMagenta"),
        QColor("green"), QColor("red"), QColor("yellow"), QColor("blue")};

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(5.f);
    glLineWidth(3.f);

    glBegin(primitiveMode);
        glColor3d(colors[0].redF(), colors[0].greenF(), colors[0].blueF());
        glVertex2d(-0.1f, 0.8f);
        glColor3d(colors[1].redF(), colors[1].greenF(), colors[1].blueF());
        glVertex2d(-0.4f, 0.6f);
        glColor3d(colors[2].redF(), colors[2].greenF(), colors[2].blueF());
        glVertex2d(-0.7f, 0.05f);
        glColor3d(colors[3].redF(), colors[3].greenF(), colors[3].blueF());
        glVertex2d(-0.6f, -0.35f);
        glColor3d(colors[4].redF(), colors[4].greenF(), colors[4].blueF());
        glVertex2d(-0.35f, -0.7f);
        glColor3d(colors[5].redF(), colors[5].greenF(), colors[5].blueF());
        glVertex2d(0.2f, -0.8f);
        glColor3d(colors[6].redF(), colors[6].greenF(), colors[6].blueF());
        glVertex2d(0.5f, -0.75f);
        glColor3d(colors[7].redF(), colors[7].greenF(), colors[7].blueF());
        glVertex2d(0.75f, -0.2f);
        glColor3d(colors[8].redF(), colors[8].greenF(), colors[8].blueF());
        glVertex2d(0.6f, 0.25f);
        glColor3d(colors[9].redF(), colors[9].greenF(), colors[9].blueF());
        glVertex2d(0.25f, 0.7f);
    glEnd();
}

void GLScene::setPrimitiveMode(GLenum mode)
{
    primitiveMode = mode;
    update();
}
