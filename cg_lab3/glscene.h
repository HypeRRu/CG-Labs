#ifndef GLSCENE_H
#define GLSCENE_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>

class GLScene: public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    GLScene(QWidget* parent = nullptr);

    void setRecursionDepth(GLint depth);
    void setStartAngle(GLdouble angle);
    void setAngleChangeCoefficient(GLdouble coefficient);
    void setStartLength(GLdouble length);
    void setLengthChangeCoefficient(GLdouble coefficient);
    void setStartWidth(GLdouble width);
    void setWidthChangeCoefficient(GLdouble coefficient);
protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
private:
    void drawTreeRecursive(GLint depth, GLdouble length, GLdouble angle, GLdouble width);

    GLint recursionDepth = 6;

    GLdouble startAngle = 40.f;
    GLdouble angleChangeCoefficient = 0.75f;

    GLdouble startLength = 0.5f;
    GLdouble lengthChangeCoefficient = 0.7f;

    GLdouble startWidth = 10.f;
    GLdouble widthChangeCoefficient = 0.7f;
};

#endif // GLSCENE_H
