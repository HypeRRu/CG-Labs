#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <QVector3D>

///! @brief camera representation
class Camera
{
public:
    Camera(
        const QPointF& screenSize,
        float speed = 0.02f,
        const QVector3D& position = { 0.f, 0.f, 3.f }
    );

    ///! @brief move camera forward and right
    void move(int forward, int right);
    ///! @brief rotate camera to look at xPos and yPos
    void rotate(float xPos, float yPos);
    ///! @brief rotate camera to look at position
    void rotate(const QPointF& position);
    ///! @brief setup mouse press position
    void mousePress(const QPointF& position);
    ///! @brief set window size
    void resize(const QPointF& size);

    inline QVector3D getPosition() const { return position_; }
    inline QMatrix4x4 getView() const { return matrix_; }
    inline QMatrix4x4 getRotation() const { return rotation_; }

private:
    ///! @brief convert degrees to radians
    inline float d2r(float degrees) const
    {
        return 3.1459265 * degrees / 180.f;
    }
    ///! @brief set front and up vectors and calculate right vector
    void setDirectionVectors(const QVector3D& front, const QVector3D& up);
    ///! @brief recalculate view and rotation matrices
    void rebuildMatrix();

    ///! @brief view matrix
    QMatrix4x4 matrix_;
    ///! @brief camera rotation matrix
    QMatrix4x4 rotation_;
    ///! @brief camera movement speed
    float speed_;
    ///! @brief camera position
    QVector3D position_;
    ///! @brief camera front direction vector
    QVector3D frontVector_;
    ///! @brief camera up direction vector
    QVector3D upVector_;
    ///! @brief camera right direction vector
    QVector3D rightVector_;
    ///! @brief mouse sensitivity for camera rotation
    float sensitivity_ = 0.01f;
    ///! @brief camera yaw
    float yaw_      = -90.f;
    ///! @brief camera pitch
    float pitch_    = 0.f;
    ///! @brief window size
    QPointF screenSize_;
    ///! @brief mouse last location after press
    QPointF lastMousePosition_;
};

#endif // CAMERA_H
