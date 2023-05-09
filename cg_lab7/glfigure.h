#ifndef GLFIGURE_H
#define GLFIGURE_H

#include <QMatrix4x4>
#include "glvertexobject.h"
#include "glmaterial.h"

class GLScene;

///! @brief figure cut info
struct CircleBaseData
{
    GLfloat radius;
    GLfloat y;
};

///! @brief EBO element
struct TriangleIndices
{
    GLuint first;
    GLuint second;
    GLuint third;
};

///! @brief figure representation
class GLFigure
{
public:
    GLFigure(const QVector<CircleBaseData>& circles);

    ///! @brief init figure: calculate polygons and set attribute info
    void init(GLScene* painter);
    ///! @brief draw figure with given fragmentation to given painter
    void draw(GLScene* painter, GLuint fragmentation = 0);
    ///! @brief set figure rotation matrix
    void setRotation(const QMatrix4x4& rotationMatrix);
    ///! @brief set figure rotation
    void setRotation(GLfloat angle, const QVector3D& rotationAxis);
    ///! @brief set figure scale matrix
    void setScale(const QMatrix4x4& scaleMatrix);
    ///! @brief set figure scale
    void setScale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ);
    ///! @brief set figure translation matrix
    void setTranslation(const QMatrix4x4& translationMatrix);
    ///! @brief set figure translation
    void setTranslation(GLfloat translationX, GLfloat translationY, GLfloat translationZ);
    ///! @brief get figure material
    inline GLMaterial& getMaterial() { return material_; }

private:
    ///! @brief calculate figure polygons and norms
    void calculatePolygons();
    ///! @brief calculate figure vertices
    void generateCircles();
    ///! @brief calculate figure vertices indices for EBO
    void generateIndices();
    ///! @brief calculate polygons norms
    void generateNorms();
    ///! @brief generate circle with given radius and Y coordinate
    void generateCircle(
        GLfloat radius,
        GLfloat y
    );
    ///! @brief set figure attribute info
    void setAttributeInfo(QOpenGLFunctions* painter);

    ///! @brief is figure has been initialized
    bool initialized_ = false;
    ///! @brief is polygons recalculation needed
    bool dirty_ = true;
    ///! @brief count of EBO elements
    GLuint indicesCount_;
    ///! @brief current figure fragmentation factor
    GLuint fragmentation_;
    ///! @brief base count of figure cut (circle) segments
    GLuint baseCircleSegmentsCount_;
    ///! @brief figure base set of cuts
    const QVector<CircleBaseData> baseCircles_;
    ///! @brief vertex object
    GLVertexObject vertexObject_;
    ///! @brief figure vertices and norms vector
    QVector<QPair<QVector3D, QVector3D>> vertices_;
    ///! @brief figure vertices indices for EBO
    QVector<TriangleIndices> indices_;
    ///! @brief figure rotation matrix
    QMatrix4x4 rotation_;
    ///! @brief figure scale matrix
    QMatrix4x4 scale_;
    ///! @brief figure translation matrix
    QMatrix4x4 translation_;
    ///! @brief figure material info
    GLMaterial material_;
};

#endif // GLFIGURE_H
