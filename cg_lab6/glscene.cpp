#include "glscene.h"

#include <QColor>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTimer>
#include <algorithm>
#include <iostream>

GLScene::GLScene(QWidget* parent):
    QOpenGLWidget{ parent }
{
    fillBaseCircles();
}


void GLScene::initializeGL()
{
    /* int opengl window */
    QColor bgc(0x2E, 0x2E, 0x2E);
    initializeOpenGLFunctions();
    glClearColor(bgc.redF(), bgc.greenF(), bgc.blueF(), bgc.alphaF());
    /* create figure and axes shader programs */
    createShaderPrograms();
    /* initialize shader programs */
    if (!figureShaderProgram_->init() || !axesShaderProgram_->init())
    {
        std::cerr << "Unable to initialize Shader Programs" << std::endl;
        std::cerr << "Figure Shader Program log: " << figureShaderProgram_->log().toStdString() << std::endl;
        std::cerr << "Axes Shader Program log: " << axesShaderProgram_->log().toStdString() << std::endl;
        return;
    }
    /* initialize vertex buffers */
    figureVertexObject_.init();
    axesVertexObject_.init();
    /* calculate and load figure and axes vertices */
    beforeUpdate();
    /* set transformations by default */
    setRotation(0.f, 0.f, 0.f);
    setScale(1.f, 1.f, 1.f);
    setTranslation(0.f, 0.f, 0.f);
    /* set wireframe mode */
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}


void GLScene::resizeGL(int w, int h)
{
    _width = w;
    _height = h;
}


void GLScene::paintGL()
{
    /* draw figure */
    figureShaderProgram_->bind();
    figureVertexObject_.bind_vao();

    glLineWidth(1.0f);
    /* draw circles */
    GLuint circleFragments = fragmentationFactor_ * baseCircleFragmentsCount_;
    GLuint circleCount = fragmentationFactor_ * (baseCircles_.size() - 1) + 1;
    GLuint offset = 0;
    for (GLuint i = 0; i < circleCount; ++i)
    {
        glDrawArrays(GL_LINE_LOOP, offset, circleFragments);
        offset += circleFragments;
    }
    /* draw lines */   
    for (GLuint i = 0; i < circleFragments; ++i)
    {
        glDrawArrays(GL_LINE_STRIP, offset, circleCount);
        offset += circleCount;
    }
    /* set figure transformations */
    {
        int rotationMatrixLocation = figureShaderProgram_->uniformLocation("rotation");
        figureShaderProgram_->setUniformValue(rotationMatrixLocation, rotationMatrix_);

        int scaleMatrixLocation = figureShaderProgram_->uniformLocation("scale");
        figureShaderProgram_->setUniformValue(scaleMatrixLocation, scaleMatrix_);

        int translationMatrixLocation = figureShaderProgram_->uniformLocation("translation");
        figureShaderProgram_->setUniformValue(translationMatrixLocation, translationMatrix_);
    }

    figureVertexObject_.unbind_vao();
    figureShaderProgram_->release();

    /* draw axes */
    axesShaderProgram_->bind();
    axesVertexObject_.bind_vao();

    glLineWidth(3.0f);
    /* set axes rotation */
    {
        int rotationMatrixLocation = axesShaderProgram_->uniformLocation("rotation");
        axesShaderProgram_->setUniformValue(rotationMatrixLocation, rotationMatrix_);
    }
    glDrawArrays(GL_LINES, 0, 6);

    axesVertexObject_.unbind_vao();
    axesShaderProgram_->release();
}


void GLScene::createShaderPrograms()
{
    QMap<QOpenGLShader::ShaderType, QString> figureShaders;
    QMap<QOpenGLShader::ShaderType, QString> axesShaders;

    figureShaders[QOpenGLShader::Vertex] = ":/shaders/figure.vs";
    figureShaders[QOpenGLShader::Fragment] = ":/shaders/figure.fs";

    axesShaders[QOpenGLShader::Vertex] = ":/shaders/axes.vs";
    axesShaders[QOpenGLShader::Fragment] = ":/shaders/axes.fs";

    figureShaderProgram_ = new GLShaderProgram(figureShaders, this);
    axesShaderProgram_ = new GLShaderProgram(axesShaders, this);
}


void GLScene::fillBaseCircles()
{
    /* base circles radiuses and Y coordinates */
    baseCircles_ = {
        { 1.00,  0.8 }, { 0.50,  0.7 }, { 0.30,  0.6 }, { 0.20,  0.5 },
        { 0.15,  0.4 }, { 0.10,  0.3 }, { 0.10,  0.2 }, { 0.10,  0.1 },
        { 0.10,  0.0 },
        { 0.10, -0.1 }, { 0.10, -0.2 }, { 0.10, -0.3 }, { 0.15, -0.4 },
        { 0.20, -0.5 }, { 0.30, -0.6 }, { 0.50, -0.7 }, { 1.00, -0.8 },
        { 1.04, -0.6 }, { 1.07, -0.4 }, { 1.09, -0.2 }, { 1.10,  0.0 },
        { 1.09,  0.2 }, { 1.07,  0.4 }, { 1.04,  0.6 }, { 1.00,  0.8 }
    };
}


void GLScene::prepareData()
{
    /* calculate circle vertices */
    prepareCircles();
    /* calculate line vertices */
    prepareLines();
    /* calculate axes vertices */
    prepareAxes();
}


void GLScene::loadData()
{
    /* load circles and lines data to figure buffer */
    loadCirclesAndLines();
    /* load axes data to axes buffer */
    loadAxes();
}


void GLScene::prepareCircles()
{
    if (!baseCircles_.size())
    {
        return;
    }
    circleVertices_.clear();

    GLuint circleFragments = fragmentationFactor_ * baseCircleFragmentsCount_;
    GLdouble radius = baseCircles_[0].radius;
    GLdouble y = baseCircles_[0].y;

    for (GLsizei i = 0; i < baseCircles_.size() - 1; ++i)
    {
        /* delta radius and Y between 2 between two adjacent circles */
        GLdouble deltaRadius = (
            baseCircles_[i + 1].radius - baseCircles_[i].radius
        ) / fragmentationFactor_;
        GLdouble deltaY = (
            baseCircles_[i + 1].y - baseCircles_[i].y
        ) / fragmentationFactor_;
        /* generate circles vertices */
        for (GLuint j = 0; j < fragmentationFactor_; ++j)
        {
            /* generate circle vertices */
            generateCircleVertices(radius, y, circleFragments);
            radius += deltaRadius;
            y += deltaY;
        }
    }
    /* generate last circle vertices */
    generateCircleVertices(radius, y, circleFragments);
}


void GLScene::prepareLines()
{
    if (!baseCircles_.size())
    {
        return;
    }
    lineVertices_.clear();

    GLdouble circleFragments = fragmentationFactor_ * baseCircleFragmentsCount_;
    GLuint circleCount = fragmentationFactor_ * (baseCircles_.size() - 1) + 1;
    /* generate lines between circles */
    for (GLuint i = 0; i < circleFragments; ++i)
    {
        for (GLuint j = 0; j < circleCount; ++j)
        {
            lineVertices_.push_back(circleVertices_[i + j * circleFragments]);
        }
    }
}


void GLScene::prepareAxes()
{
    axesVertices_.clear();

    /* x axis */
    axesVertices_.push_back({
        { 0.0, 0.0, 0.0 },
        { 0.8, 0.2, 0.2 }
    });
    axesVertices_.push_back({
        { 0.1, 0.0, 0.0 },
        { 0.8, 0.2, 0.2 }
    });

    /* y axis */
    axesVertices_.push_back({
        { 0.0, 0.0, 0.0 },
        { 0.2, 0.8, 0.2 }
    });
    axesVertices_.push_back({
        { 0.0, 0.1, 0.0 },
        { 0.2, 0.8, 0.2 }
    });

    /* z axis */
    axesVertices_.push_back({
        { 0.0, 0.0, 0.0 },
        { 0.2, 0.2, 0.8 }
    });
    axesVertices_.push_back({
        { 0.0, 0.0, 0.1 },
        { 0.2, 0.2, 0.8 }
    });
}


void GLScene::generateCircleVertices(
    GLdouble radius,
    GLdouble y,
    GLdouble circleFragments
)
{
    GLdouble angle = 0.f;
    GLdouble deltaAngle = 2.0f * 3.14159265f / circleFragments;
    /* generate and write single circle with radius and Y vertex data */
    for (GLuint k = 0; k < circleFragments; ++k)
    {
        circleVertices_.emplaceBack(
            radius * cos(angle),
            y,
            radius * sin(angle)
            );
        angle += deltaAngle;
    }
}


void GLScene::loadCirclesAndLines()
{
    /* load circles and lines data to figure buffer */
    figureVertexObject_.bind_vao();
    figureVertexObject_.loadVertices(circleVertices_ + lineVertices_);
    figureVertexObject_.setupVertexAttribute(
        this, 0, 3, GL_FLOAT, GL_TRUE,
        sizeof(QVector3D), nullptr
    );
    figureVertexObject_.unbind_vao();
}


void GLScene::loadAxes()
{
    /* load axes data to axes buffer */
    axesVertexObject_.bind_vao();
    axesVertexObject_.loadVertices(axesVertices_);
    axesVertexObject_.setupVertexAttribute(
        this, 0, 3, GL_FLOAT, GL_TRUE,
        sizeof(QVector3D) * 2,
        nullptr
    );
    axesVertexObject_.setupVertexAttribute(
        this, 1, 3, GL_FLOAT, GL_TRUE,
        sizeof(QVector3D) * 2,
        reinterpret_cast<void*>(sizeof(QVector3D))
    );
    axesVertexObject_.unbind_vao();
}


void GLScene::beforeUpdate()
{
    prepareData();
    loadData();
}


void GLScene::setFragmentationFactor(GLuint factor)
{
    fragmentationFactor_ = factor;
    beforeUpdate();
    update();
}


void GLScene::setRotation(GLdouble x, GLdouble y, GLdouble z)
{
    rotationMatrix_.setToIdentity();
    rotationMatrix_.rotate(x, 1.f, 0.f, 0.f);
    rotationMatrix_.rotate(y, 0.f, 1.f, 0.f);
    rotationMatrix_.rotate(z, 0.f, 0.f, 1.f);

    update();
}


void GLScene::setScale(GLdouble x, GLdouble y, GLdouble z)
{
    scaleMatrix_.setToIdentity();
    scaleMatrix_.scale(x, y, z);

    update();
}


void GLScene::setTranslation(GLdouble x, GLdouble y, GLdouble z)
{
    translationMatrix_.setToIdentity();
    translationMatrix_.translate(x, y, z);

    update();
}
