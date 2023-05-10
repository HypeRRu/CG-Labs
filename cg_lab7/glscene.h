#ifndef GLSCENE_H
#define GLSCENE_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <memory>

#include "glshaderprogram.h"
#include "glfigure.h"
#include "gllighting.h"
#include "camera.h"

///! @brief camera projection type
enum class GLProjectionType
{
    Perspective,
    Orthographic
};

///! @brief OpenGL scene representation
class GLScene: public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    GLScene(QWidget* parent = nullptr);

    virtual void keyPressEvent(QKeyEvent* event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;

    ///! @brief set camera projection type
    void setProjectionType(GLProjectionType type);

    inline GLShaderProgram* getFigureShaderProgram() { return figureShaderProgram_; }
    inline GLLighting& getLighting() { return lighting_; }
    inline QVector<std::shared_ptr<GLFigure>>& getFigures() { return figures_; }
    inline std::shared_ptr<GLFigure> getFigure(ssize_t index) { return figures_.at(index); }

protected:
    ///! @brief initialize OpenGL window
    virtual void initializeGL() override;
    ///! @brief resize OpenGL window
    virtual void resizeGL(int w, int h) override;
    ///! @brief draw scene
    virtual void paintGL() override;

private:
    ///! @brief create OpenGL shader programs for figures, axes and light source
    void createShaderProgram();
    ///! @brief generate figures base cuts
    void generateFigures();
    ///! @brief generate axes vertices
    void generateAxes();
    ///! @brief convert degrees to radians
    inline float d2r(float degrees) const
    {
        return 3.1459265 * degrees / 180.f;
    }

    ///! @brief scene width
    GLfloat width_;
    ///! @brief scene height
    GLfloat height_;
    ///! @brief figure shader program
    GLShaderProgram* figureShaderProgram_ = nullptr;
    ///! @brief scene lighting params
    GLLighting lighting_;
    ///! @brief axes shader program
    GLShaderProgram* axesShaderProgram_ = nullptr;
    ///! @brief axes vertex object
    GLVertexObject axesVertexObject_;
    ///! @brief light source shader program
    GLShaderProgram* lightSourceShaderProgram_ = nullptr;
    ///! @brief light source representation
    std::shared_ptr<GLFigure> lightSource_;
    ///! @brief detalization factor
    GLuint fragmentationFactor_ = 5;
    ///! @brief camera settings
    Camera camera_;
    ///! @brief camera projection type
    GLProjectionType projection_ = GLProjectionType::Perspective;
    ///! @brief model matrix
    QMatrix4x4 modelMatrix_;
    ///! @brief projection matrix
    QMatrix4x4 projectionMatrix_;
    ///! @brief figures representations
    QVector<std::shared_ptr<GLFigure>> figures_;
    ///! @brief axes vertices vector
    QVector<QPair<QVector3D, QVector3D>> axesVertices_;
};

#endif // GLSCENE_H
