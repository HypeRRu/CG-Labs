#ifndef GLMATERIAL_H
#define GLMATERIAL_H

#include <QColor>

class QOpenGLShaderProgram;

///! @brief material representation
class GLMaterial
{
public:
    GLMaterial();
    GLMaterial(
        const QColor& diffuse,
        const QColor& specular,
        float shininess = 16.f,
        float ambientStrength = 0.4f
    );

    ///! @brief set material diffuse light color
    void setDiffuseColor(const QColor& color);
    ///! @brief get material diffuse light color
    QColor getDiffuseColor() const;
    ///! @brief set material specular light color
    void setSpecularColor(const QColor& color);
    ///! @brief get material specular light color
    QColor getSpecularColor() const;
    ///! @brief set material shininess
    void setShininess(float shininess);
    ///! @brief get material shininess
    float getShininess() const;
    ///! @brief set material ambient light strength
    void setAmbientStrength(float strength);
    ///! @brief get material ambient light strength
    float getAmbientStrength() const;
    ///! @brief load material info to the shader program
    void apply(QOpenGLShaderProgram* shaderProgram) const;

private:
    ///! @brief material diffuse light color
    QColor diffuse_;
    ///! @brief material specular light color
    QColor specular_;
    ///! @brief material shininess
    float shininess_;
    ///! @brief material ambient light strength
    float ambientStrength_;
};

#endif // GLMATERIAL_H
