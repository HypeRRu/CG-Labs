#ifndef GLLIGHTING_H
#define GLLIGHTING_H

#include <QMap>
#include <QVector3D>
#include <QMatrix4x4>
#include <QColor>

class QOpenGLShaderProgram;
class QOpenGLFunctions;

///! @brief light type
enum class GLLightingType
{
    Point,
    Directional,
    Spot
};

///! @brief lighting represenation
class GLLighting
{
public:
    GLLighting(
        GLLightingType type,
        const QVector3D& position,
        const QVector3D& direction,
        const QColor& ambient = Qt::cyan,
        const QColor& diffuse = Qt::yellow,
        const QColor& specular = Qt::white
    );

    ///! @brief set light type
    void setType(GLLightingType type);
    ///! @brief get light type
    GLLightingType getType() const;
    ///! @brief set light source position
    void setPosition(const QVector3D& position);
    ///! @brief get light source position
    QVector3D getPosition() const;
    ///! @brief set light direction
    void setDirection(const QVector3D& direction);
    ///! @brief get light direction
    QVector3D getDirection() const;
    ///! @brief set ambient light color
    void setAmbientColor(const QColor& color);
    ///! @brief get ambient light color
    QColor getAmbientColor() const;
    ///! @brief set diffuse light color
    void setDiffuseColor(const QColor& color);
    ///! @brief get diffuse light color
    QColor getDiffuseColor() const;
    ///! @brief set specular light color
    void setSpecularColor(const QColor& color);
    ///! @brief get specular light color
    QColor getSpecularColor() const;
    ///! @brief set attenuation coefficients: constant, linear and quadratic
    void setAttenuation(const QVector3D& attenuation);
    ///! @brief get attenuation coefficients: constant, linear and quadratic
    QVector3D getAttenuation() const;
    ///! @brief set spot light cut offset
    void setCutOff(float cutOff);
    ///! @brief get spot light cut offset
    float getCutOff() const;
    ///! @brief set spot light outer cut offset
    void setOuterCutOff(float outerCutOff);
    ///! @brief get spot light outer cut offset
    float getOuterCutOff() const;
    ///! @brief load lighting info to the shader program
    void apply(QOpenGLShaderProgram* shaderProgram) const;

private:
    ///! @brief convert degrees to radians
    inline float d2r(float degrees) const
    {
        return 3.1459265 * degrees / 180.f;
    }

    ///! @brief current light type
    GLLightingType type_;
    ///! @brief light source position
    QVector3D position_;
    ///! @brief light direction
    QVector3D direction_;
    ///! @brief ambient light color
    QColor ambient_;
    ///! @brief diffuse light color
    QColor diffuse_;
    ///! @brief specular light color
    QColor specular_;
    ///! @brief attenuation coefficients: constant, linear and quadratic
    QVector3D attenuation_;
    ///! @brief spot light cut offset
    float cutOff_;
    ///! @brief spot light outer cut offset
    float outerCutOff_;
};

#endif // GLLIGHTING_H
