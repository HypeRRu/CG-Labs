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
    frameWidth = w;
    frameHeight = h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void GLScene::paintGL()
{
    // enable test modes
    if (scissorTestEnabled)
        glEnable(GL_SCISSOR_TEST);
    if (alphaTestEnabled)
        glEnable(GL_ALPHA_TEST);
    if (blendTestEnabled)
        glEnable(GL_BLEND);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPointSize(5.f);
    glLineWidth(3.f);    

    glScissor(
        scissorXRate * frameWidth,
        scissorYRate * frameHeight,
        scissorWRate * (1.f - scissorXRate) * frameWidth,
        scissorHRate * (1.f - scissorYRate) * frameHeight
    );
    glAlphaFunc(alphaTest, alpha);
    glBlendFunc(sFactorBlend, dFactorBlend);

    glBegin(primitiveMode);
        setPoints();
    glEnd();

    // disable test modes
    if (scissorTestEnabled)
        glDisable(GL_SCISSOR_TEST);
    if (alphaTestEnabled)
        glDisable(GL_ALPHA_TEST);
    if (blendTestEnabled)
        glDisable(GL_BLEND);
}

void GLScene::setPoints()
{
    QColor colors[10] = {
        QColor("cyan"), QColor("magenta"), QColor("darkGreen"),
        QColor("darkRed"), QColor("darkCyan"), QColor("darkMagenta"),
        QColor("green"), QColor("red"), QColor("yellow"), QColor("blue")};

    glColor4d(colors[0].redF(), colors[0].greenF(), colors[0].blueF(), 0.1f);
    glVertex2d(-0.1f, 0.8f);
    glColor4d(colors[1].redF(), colors[1].greenF(), colors[1].blueF(), 0.2f);
    glVertex2d(-0.4f, 0.6f);
    glColor4d(colors[2].redF(), colors[2].greenF(), colors[2].blueF(), 0.3f);
    glVertex2d(-0.7f, 0.05f);
    glColor4d(colors[3].redF(), colors[3].greenF(), colors[3].blueF(), 0.4f);
    glVertex2d(-0.6f, -0.35f);
    glColor4d(colors[4].redF(), colors[4].greenF(), colors[4].blueF(), 0.5f);
    glVertex2d(-0.35f, -0.7f);
    glColor4d(colors[5].redF(), colors[5].greenF(), colors[5].blueF(), 0.6f);
    glVertex2d(0.2f, -0.8f);
    glColor4d(colors[6].redF(), colors[6].greenF(), colors[6].blueF(), 0.7f);
    glVertex2d(0.5f, -0.75f);
    glColor4d(colors[7].redF(), colors[7].greenF(), colors[7].blueF(), 0.8f);
    glVertex2d(0.75f, -0.2f);
    glColor4d(colors[8].redF(), colors[8].greenF(), colors[8].blueF(), 0.9f);
    glVertex2d(0.6f, 0.25f);
    glColor4d(colors[9].redF(), colors[9].greenF(), colors[9].blueF(), 1.0f);
    glVertex2d(0.25f, 0.7f);
}

void GLScene::setPrimitiveMode(GLenum mode)
{
    primitiveMode = mode;
    update();
}

void GLScene::setAlphaTestMode(GLenum mode)
{
    alphaTest = mode;
    update();
}

void GLScene::setAlphaRef(GLdouble ref)
{
    alpha = ref;
    update();
}

void GLScene::setBlendSFactor(GLenum factor)
{
    sFactorBlend = factor;
    update();
}

void GLScene::setBlendDFactor(GLenum factor)
{
    dFactorBlend = factor;
    update();
}

void GLScene::setScissorXRate(GLdouble rate)
{
    scissorXRate = rate;
    update();
}

void GLScene::setScissorYRate(GLdouble rate)
{
    scissorYRate = rate;
    update();
}

void GLScene::setScissorWRate(GLdouble rate)
{
    scissorWRate = rate;
    update();
}

void GLScene::setScissorHRate(GLdouble rate)
{
    scissorHRate = rate;
    update();
}
