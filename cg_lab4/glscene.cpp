#include "glscene.h"

#include <QColor>
#include <QMouseEvent>
#include <QKeyEvent>
#include <algorithm>

GLScene::GLScene(QWidget* parent):
    QOpenGLWidget{ parent },
    _spline{_controlPoints}
{}


void GLScene::initializeGL()
{
    QColor bgc(255, 255, 255);
    initializeOpenGLFunctions();
    glClearColor(bgc.redF(), bgc.greenF(), bgc.blueF(), bgc.alphaF());
}


void GLScene::resizeGL(int w, int h)
{
    _width = w;
    _height = h;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void GLScene::paintGL()
{
    drawSpline();
    int selectedPointIndex = getIndexOfPoint(_selectedPoint);
    for (int i = 0; i < _controlPoints.size(); ++i)
    {
        if (i == selectedPointIndex)
        {
            drawPoint(_controlPoints[i], 8.f, Qt::green);
            drawPoint(_controlPoints[i], 6.f, Qt::white);
        }
        drawPoint(_controlPoints[i], 4.f, Qt::red);
    }
}


void GLScene::drawSpline()
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

    double step = 0.00001;
    glBegin(GL_LINE_STRIP);
        for (
            double x = _controlPoints.first().x();
            x <= _controlPoints.last().x();
            x += step
        )
        {
            glVertex2d(x, _spline.getValue(x));
        }
    glEnd();
}


void GLScene::drawPoint(const QPointF& position, double size, const QColor& color)
{
    glColor3d(color.redF(), color.greenF(), color.blueF());
    glPointSize(size);
    glBegin(GL_POINTS);
        glVertex2d(
            position.x(),
            position.y()
        );
    glEnd();
}


int GLScene::getIndexOfPoint(const QPointF& point) const
{
    for (int i = 0; i < _controlPoints.size(); ++i)
    {
        if (
            point.x() == _controlPoints.at(i).x() &&
            point.y() == _controlPoints.at(i).y()
        )
        {
            return i;
        }
    }
    return -1;
}


void GLScene::mousePressEvent(QMouseEvent* event)
{
    double accuracy = 0.01;
    QPointF topLeftPosition {
        2 * event->position().x() / _width - 1 - accuracy,
        -2 * event->position().y() / _height + 1 - accuracy
    };
    QRectF container(topLeftPosition, QSizeF {2*accuracy, 2*accuracy});

    for (int i = 0; i < _controlPoints.size(); ++i)
    {
        if (container.contains(_controlPoints[i]))
        {
            _selectedPoint = _controlPoints[i];
            update();
            QWidget::mousePressEvent(event);
            return;
        }
    }
    update();
    QWidget::mousePressEvent(event);
}


void GLScene::mouseDoubleClickEvent(QMouseEvent* event)
{
    QPointF position {
        2 * event->position().x() / _width - 1,
        -2 * event->position().y() / _height + 1
    };
    _controlPoints.push_back(position);

    _selectedPoint = {-2.f, -2.f};
    update();
    QWidget::mouseDoubleClickEvent(event);
}


void GLScene::mouseMoveEvent(QMouseEvent* event)
{
    int selectedPointIndex = -1;
    if (
        !(event->buttons() & Qt::LeftButton) ||
        (selectedPointIndex = getIndexOfPoint(_selectedPoint)) < 0
    )
    {
        QWidget::mouseMoveEvent(event);
        return;
    }

    QPointF position {
        2 * event->position().x() / _width - 1,
        -2 * event->position().y() / _height + 1
    };
    _controlPoints[selectedPointIndex].setX(position.x());
    _controlPoints[selectedPointIndex].setY(position.y());
    _selectedPoint = position;

    update();
    QWidget::mouseMoveEvent(event);
}


void GLScene::mouseReleaseEvent(QMouseEvent* event)
{
    _selectedPoint = {-2.f, -2.f};
    update();
    QWidget::mouseReleaseEvent(event);
}


void GLScene::keyPressEvent(QKeyEvent* event)
{
    int selectedPointIndex = -1;
    if (
        event->key() != Qt::Key_D ||
        (selectedPointIndex = getIndexOfPoint(_selectedPoint)) < 0
    )
    {
        QWidget::keyPressEvent(event);
        return;
    }

    _controlPoints.removeAt(selectedPointIndex);
    _selectedPoint = {-2.f, -2.f};
    update();
    QWidget::keyPressEvent(event);
}
