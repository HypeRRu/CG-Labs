#include "glscene.h"

#include <QColor>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <algorithm>
#include <iostream>

GLScene::GLScene(QWidget* parent):
    QOpenGLWidget{ parent },
    _spline{_controlPoints},
    _ebo{QOpenGLBuffer::IndexBuffer},
    _timer{new QTimer}
{}


GLScene::~GLScene()
{
    _vao.destroy();
    _vbo.destroy();
    _ebo.destroy();
    _timer->stop();
    delete _timer;
}


void GLScene::initializeGL()
{
    QColor bgc(255, 255, 255);
    initializeOpenGLFunctions();
    glClearColor(bgc.redF(), bgc.greenF(), bgc.blueF(), bgc.alphaF());

    if (!initShaderProgram())
    {
        std::cerr << _shaderProgram.log().toStdString() << std::endl;
        return;
    }
    generateControlPoints();
    calculateSplinePoints();
    bindVertices();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    connect(_timer, &QTimer::timeout, this, &GLScene::updateTimer);
    _timer->start(30);
}


void GLScene::resizeGL(int w, int h)
{
    _width = w;
    _height = h;

    glViewport(0, 0, w, h);

    QMatrix4x4 transformMatrix;
    transformMatrix.setToIdentity();
    transformMatrix.rotate(50.f, 1.f, 0.f, 0.f);

    int matrixLocation = _shaderProgram.uniformLocation("transformations");
    _shaderProgram.setUniformValue(matrixLocation, transformMatrix);
}


void GLScene::paintGL()
{
    _vao.bind();
    _vbo.bind();
    _ebo.bind();
    _shaderProgram.bind();
    int vertexLocation = _shaderProgram.attributeLocation("vPos");
    int normalLocation = _shaderProgram.attributeLocation("vNorm");

    _shaderProgram.enableAttributeArray(vertexLocation);
    _shaderProgram.setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3, sizeof(GLfloat) * 6);

    _shaderProgram.enableAttributeArray(normalLocation);
    _shaderProgram.setAttributeBuffer(normalLocation, GL_FLOAT, 3 * sizeof(GLfloat), 3, sizeof(GLfloat) * 6);

    int timeLocation = _shaderProgram.uniformLocation("time");
    _shaderProgram.setUniformValue(timeLocation, _time);

    glDrawElements(GL_TRIANGLE_STRIP, 6 * (_splinePoints.size() - 1), GL_UNSIGNED_SHORT, nullptr);
}


bool GLScene::initShaderProgram()
{
    _vao.create();
    _vao.bind();

    _vbo.create();
    _ebo.create();
    // compile vertex shader
    if (
        !_shaderProgram.addShaderFromSourceFile(
            QOpenGLShader::Vertex,
            ":/shaders/lab5.vs"
        )
    )
    {
        return false;
    }
    // compile fragment shader
    if (
        !_shaderProgram.addShaderFromSourceFile(
            QOpenGLShader::Fragment,
            ":/shaders/lab5.fs"
        )
    )
    {
        return false;
    }
    // link shaders to program
    if (!_shaderProgram.link())
    {
        return false;
    }
    // bind shader program to use
    if (!_shaderProgram.bind())
    {
        return false;
    }
    return true;
}


void GLScene::generateControlPoints()
{
    _controlPoints.emplaceBack(-0.84,  -0.40);
    _controlPoints.emplaceBack(-0.77, -0.25);
    _controlPoints.emplaceBack(-0.53,  0.00);
    _controlPoints.emplaceBack(-0.17, -0.32);
    _controlPoints.emplaceBack( 0.26,  0.15);
    _controlPoints.emplaceBack( 0.62, -0.27);
    _controlPoints.emplaceBack( 0.79,  0.12);
    //_controlPoints.emplaceBack( 0.88,  0.21);
}


void GLScene::calculateSplinePoints()
{
    std::sort(
        _controlPoints.begin(),
        _controlPoints.end(),
        [](const QPointF& a, const QPointF& b){
            return a.x() < b.x();
        }
    );

    _spline.flush();
    if (_controlPoints.size() < 3)
        return;

    _spline.build();

    double step = 0.0001;
    for (
        double x = _controlPoints.first().x();
        x <= _controlPoints.last().x();
        x += step
    )
    {
        _splinePoints.emplaceBack(x, _spline.getValue(x));
    }
}


void GLScene::bindVertices()
{
    int vCount = 12 * _splinePoints.size();
    int iCount = 6 * (_splinePoints.size() - 1);
    GLfloat* vertices = new GLfloat[vCount];
    GLushort* indices = new GLushort[iCount];

    // copy verticies to buffer
    for (GLushort i = 0; i < _splinePoints.size(); ++i)
    {
        // {x, y, 0, n1}
        vertices[12 * i + 0]  = _splinePoints[i].x();
        vertices[12 * i + 1]  = _splinePoints[i].y();
        vertices[12 * i + 2]  = 0.f;
        // {x, y, -1, n2}
        vertices[12 * i + 6]  = _splinePoints[i].x();
        vertices[12 * i + 7]  = _splinePoints[i].y();
        vertices[12 * i + 8]  = -1.f;
    }
    GLfloat dx1, dx2, dy1, dy2, dz1, dz2;
    // copy indices to buffer
    for (GLushort i = 0; i < _splinePoints.size() - 1; ++i)
    {
        // add indices to array
        indices[6 * i + 0] = 2 * i + 0;
        indices[6 * i + 1] = 2 * i + 2;
        indices[6 * i + 2] = 2 * i + 1;
        indices[6 * i + 3] = 2 * i + 3;
        indices[6 * i + 4] = 2 * i + 0;
        indices[6 * i + 5] = 2 * i + 2;

        // calculate normals
        dx1 = _splinePoints[i + 1].x() - _splinePoints[i].x();
        dx2 = 0.f;
        dy1 = _splinePoints[i + 1].y() - _splinePoints[i].y();
        dy2 = 0.f;
        dz1 = 0.f;
        dz2 = -1.f;

        vertices[12 * i + 3] = dy1 * dz2 - dy2 * dz1;
        vertices[12 * i + 9] = dy1 * dz2 - dy2 * dz1;
        vertices[12 * i + 4] = -(dx1 * dz2 - dx2 * dz1);
        vertices[12 * i + 10] = -(dx1 * dz2 - dx2 * dz1);
        vertices[12 * i + 5] = dx1 * dy2 - dx2 * dy1;
        vertices[12 * i + 11] = dx1 * dy2 - dx2 * dy1;
    }
    vertices[2 * iCount + 3] = dy1 * dz2 - dy2 * dz1;
    vertices[2 * iCount + 9] = dy1 * dz2 - dy2 * dz1;
    vertices[2 * iCount + 4] = -(dx1 * dz2 - dx2 * dz1);
    vertices[2 * iCount + 10] = -(dx1 * dz2 - dx2 * dz1);
    vertices[2 * iCount + 5] = dx1 * dy2 - dx2 * dy1;
    vertices[2 * iCount + 11] = dx1 * dy2 - dx2 * dy1;
    // fill vbo and ebo
    _vbo.bind();
    _vbo.allocate(vertices, sizeof(GLfloat) * vCount);

    _ebo.bind();
    _ebo.allocate(indices, sizeof(GLushort) * iCount);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 6, reinterpret_cast<void*>(sizeof(GLfloat) * 3));

    _vbo.release();
    _ebo.release();
    delete [] vertices;
    delete [] indices;
}


void GLScene::updateTimer()
{
    _time += _step;
    if (_time > 1000.f)
        _time = 0.f;
    update();
}
