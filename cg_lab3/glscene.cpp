#include "glscene.h"

#include <QColor>

GLScene::GLScene(QWidget* parent):
    QOpenGLWidget{ parent }
{}

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
    glColor3d(0.545f, 0.270f, 0.075f);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glTranslatef(0.f, -0.9f, 0.f);
        drawTreeRecursive(0, startLength, startAngle, startWidth);
    glPopMatrix();
}

void GLScene::drawTreeRecursive(GLint depth, GLdouble length, GLdouble angle, GLdouble width)
{
    /* check recursion depth limit */
    if (depth >= recursionDepth)
        return;
    /* setup brush */
    glLineWidth(width);
    /* draw single line */
    glBegin(GL_LINES);
        glVertex2d(0.f, 0.f);
        glVertex2d(0.f, length);
    glEnd();
    /* draw left subtree */
    glPushMatrix();
        glTranslatef(0.f, length, 0.f);
        glRotatef(angle, 0.f, 0.f, 1.f); // rotate to the angle anti-clockwise around z axis
        drawTreeRecursive(
            depth + 1,
            length * lengthChangeCoefficient,
            angle * angleChangeCoefficient,
            width * widthChangeCoefficient
        );
    glPopMatrix();
    /* draw right subtree */
    glPushMatrix();
        glTranslatef(0.f, length, 0.f);
        glRotatef(-angle, 0.f, 0.f, 1.f); // rotate to the angle clockwise around z axis
        drawTreeRecursive(
            depth + 1,
            length * lengthChangeCoefficient,
            -angle * angleChangeCoefficient,
            width * widthChangeCoefficient
        );
    glPopMatrix();
}

void GLScene::setRecursionDepth(GLint depth)
{
    recursionDepth = depth;
    update();
}

void GLScene::setStartAngle(GLdouble angle)
{
    startAngle = angle;
    update();
}

void GLScene::setAngleChangeCoefficient(GLdouble coefficient)
{
    angleChangeCoefficient = coefficient;
    update();
}

void GLScene::setStartLength(GLdouble length)
{
    startLength = length;
    update();
}

void GLScene::setLengthChangeCoefficient(GLdouble coefficient)
{
    lengthChangeCoefficient = coefficient;
    update();
}

void GLScene::setStartWidth(GLdouble width)
{
    startWidth = width;
    update();
}

void GLScene::setWidthChangeCoefficient(GLdouble coefficient)
{
    widthChangeCoefficient = coefficient;
    update();
}
