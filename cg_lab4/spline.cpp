#include "spline.h"

//#define NDEBUG
#include <cassert>
#include <QPair>
#include <QtMath>

Spline::Spline(const QVector<QPointF>& points):
    _points{ points }
{}


void Spline::build()
{
    _coefficients.resize(_points.size());
    _forward_traverse();
    _backward_traverse();
    _calculate_abd_coefficients();
}


void Spline::flush()
{
    _forward_traverse_coefficients.clear();
    _coefficients.clear();
}


double Spline::getValue(double x) const
{
    for (int i = 1; i < _points.size(); ++i)
    {
        if (x <= _points.at(i).x())
        {
            double xdiff = (x - _points.at(i - 1).x());
            return  _coefficients.at(i).a * qPow(xdiff, 0) +
                    _coefficients.at(i).b * qPow(xdiff, 1) +
                    _coefficients.at(i).c * qPow(xdiff, 2) +
                    _coefficients.at(i).d * qPow(xdiff, 3);
        }
    }
    return 0.f;
}


void Spline::_forward_traverse()
{
    double k = 0.f;
    double l = 0.f;

    _forward_traverse_coefficients.emplace_back(0, 0);
    _forward_traverse_coefficients.emplace_back(k, l);
    for (int i = 2; i < _points.size(); ++i)
    {
        double denominator = _s(i) - _h(i - 1) * l;
        double new_k = (_r(i) - _h(i - 1) * k) / denominator;
        double new_l = _h(i) / denominator;
        _forward_traverse_coefficients.emplace_back(new_k, new_l);
        k = new_k;
        l = new_l;
    }
}


void Spline::_backward_traverse()
{
    int n = _forward_traverse_coefficients.size() - 1;
    _coefficients[n].c = _forward_traverse_coefficients.at(n).x();
    for (int i = n - 1; i > 1; --i)
    {
        _coefficients[i].c =
            _forward_traverse_coefficients.at(i).x() -
            _forward_traverse_coefficients.at(i).y() * _coefficients[i + 1].c;
    }
}


void Spline::_calculate_abd_coefficients()
{
    for (int i = 1; i < _points.size(); ++i)
    {
        _coefficients[i].a = _points.at(i - 1).y();

        if (i < _points.size() - 1)
        {
            _coefficients[i].b = (
                _points.at(i).y() - _points.at(i - 1).y()
            ) / _h(i) - (
                _coefficients[i + 1].c + 2 * _coefficients[i].c
            ) * _h(i) / 3;
        } else
        {
            _coefficients[i].b = (
                _points.at(i).y() - _points.at(i - 1).y()
            ) / _h(i) - (2 * _coefficients[i].c) * _h(i) / 3;
        }

        if (i < _points.size() - 1)
        {
            _coefficients[i].d = (
                _coefficients[i + 1].c - _coefficients[i].c
            ) / (3 * _h(i));
        } else
        {
            _coefficients[i].d = -_coefficients[i].c / (3 * _h(i));
        }
    }
}


double Spline::_h(int i) const
{
    assert(i >= 1 && "h: i >= 1");
    assert(i < _points.size() && "h: i <= n");
    return _points.at(i).x() - _points.at(i - 1).x();
}


double Spline::_s(int i) const
{
    assert(i >= 2 && "s: i >= 2");
    assert(i < _points.size() && "s: i <= n");
    return 2 * (_h(i) + _h(i - 1));
}

double Spline::_r(int i) const
{
    assert(i >= 2 && "r: i >= 2");
    assert(i < _points.size() && "r: i <= n");
    return 3 * (
        (_points.at(i).y() - _points.at(i - 1).y()) / _h(i) -
        (_points.at(i - 1).y() - _points.at(i - 2).y()) / _h(i - 1)
    );
}
