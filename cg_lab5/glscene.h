#ifndef GLSCENE_H
#define GLSCENE_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QPointF>
#include <QTimer>
#include "spline.h"

class GLScene: public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    GLScene(QWidget* parent = nullptr);
    ~GLScene();
protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
private: 
    bool initShaderProgram();
    void generateControlPoints();
    void calculateSplinePoints();
    void bindVertices();

    void updateTimer();

    double _width;
    double _height;

    QVector<QPointF> _controlPoints;
    Spline _spline;
    QVector<QPointF> _splinePoints;
    QOpenGLShaderProgram _shaderProgram;
    QOpenGLVertexArrayObject _vao;
    QOpenGLBuffer _vbo;
    QOpenGLBuffer _ebo;

    QTimer* _timer;
    GLfloat _time = 0.f;
    GLfloat _step = 0.1f;
};

#endif // GLSCENE_H
