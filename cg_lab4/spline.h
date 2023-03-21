#ifndef SPLINE_H
#define SPLINE_H

#include <QVector>
#include <QPointF>

class Spline
{
public:
    Spline(const QVector<QPointF>& points);
    void build();
    void flush();
    double getValue(double x) const;
private:
    double _h(int i) const;
    double _s(int i) const;
    double _r(int i) const;

    void _forward_traverse();
    void _backward_traverse();
    void _calculate_abd_coefficients();

    struct Coefficients
    {
        double a;
        double b;
        double c;
        double d;
    };

    const QVector<QPointF>& _points;
    QVector<Spline::Coefficients> _coefficients;
    QVector<QPointF> _forward_traverse_coefficients;
};

#endif // SPLINE_H
