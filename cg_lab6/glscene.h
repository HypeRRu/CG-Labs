#ifndef GLSCENE_H
#define GLSCENE_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>

#include "glshaderprogram.h"
#include "glvertexobject.h"

struct CircleBaseData
{
    GLdouble radius;
    GLdouble y;
};

class GLScene: public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    GLScene(QWidget* parent = nullptr);

    void beforeUpdate();
    void setFragmentationFactor(GLuint factor);
    void setRotation(GLdouble x, GLdouble y, GLdouble z);
    void setScale(GLdouble x, GLdouble y, GLdouble z);
    void setTranslation(GLdouble x, GLdouble y, GLdouble z);
protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
private:
    void createShaderPrograms();
    void prepareData();
    void loadData();

    void prepareCircles();
    void prepareLines();
    void prepareAxes();

    void generateCircleVertices(
        GLdouble radius,
        GLdouble y,
        GLdouble circleFragments
    );

    void loadCirclesAndLines();
    void loadAxes();

    void fillBaseCircles();

    GLdouble _width;
    GLdouble _height;

    GLShaderProgram* figureShaderProgram_ = nullptr;
    GLVertexObject figureVertexObject_;

    GLShaderProgram* axesShaderProgram_ = nullptr;
    GLVertexObject axesVertexObject_;

    GLuint fragmentationFactor_ = 1;
    GLuint baseCircleFragmentsCount_ = 16;

    QMatrix4x4 rotationMatrix_;
    QMatrix4x4 scaleMatrix_;
    QMatrix4x4 translationMatrix_;

    QVector<CircleBaseData> baseCircles_;
    QVector<QVector3D> circleVertices_;
    QVector<QVector3D> lineVertices_;
    QVector<QPair<QVector3D, QVector3D>> axesVertices_;
};

#endif // GLSCENE_H
