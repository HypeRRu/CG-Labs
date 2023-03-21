#ifndef GLSCENE_H
#define GLSCENE_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QPointF>
#include "spline.h"

class GLScene: public QOpenGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    GLScene(QWidget* parent = nullptr);

    virtual void mousePressEvent(QMouseEvent* event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent* event) override;
    virtual void mouseReleaseEvent(QMouseEvent* event) override;
    virtual void keyPressEvent(QKeyEvent* event) override;
protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w, int h) override;
    virtual void paintGL() override;
private:
    void drawSpline();
    void drawPoint(const QPointF& position, double size = 4.f, const QColor& color = Qt::red);
    int getIndexOfPoint(const QPointF& point) const;

    double _width;
    double _height;

    QVector<QPointF> _controlPoints;
    QPointF _selectedPoint {-2.f, -2.f};
    Spline _spline;
};

#endif // GLSCENE_H
