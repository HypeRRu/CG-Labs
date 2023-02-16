#ifndef GLSCENE_H
#define GLSCENE_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>

class GLScene: public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    GLScene(QWidget* parent = nullptr);

    void setPrimitiveMode(GLenum mode);

    void setAlphaTestMode(GLenum mode);
    void setAlphaRef(GLdouble ref);

    void setBlendSFactor(GLenum factor);
    void setBlendDFactor(GLenum factor);

    void setScissorXRate(GLdouble rate);
    void setScissorYRate(GLdouble rate);
    void setScissorWRate(GLdouble rate);
    void setScissorHRate(GLdouble rate);
protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
private:
    void setPoints();

    GLint frameWidth        = 0;
    GLint frameHeight       = 0;

    GLenum primitiveMode    = GL_POINTS;

    bool alphaTestEnabled   = true;
    GLenum alphaTest        = GL_ALWAYS;
    // from 0 to 1
    GLdouble alpha          = 0.5f;

    bool blendTestEnabled   = true;
    GLenum sFactorBlend     = GL_ONE;
    GLenum dFactorBlend     = GL_ZERO;

    bool scissorTestEnabled = true;
    // from 0 to 1
    GLdouble scissorXRate   = 0.f;
    GLdouble scissorYRate   = 0.f;
    GLdouble scissorWRate   = 1.f;
    GLdouble scissorHRate   = 1.f;
};

#endif // GLSCENE_H
