#include <iostream>
#include <chrono>
#include <random>
#include <sstream>
#include <algorithm>
#include "geom3dlib.h"

bool isDebug = false;

Circle::Circle(const double _radius)
{
  if (_radius < 0)
    throw range_error("Значение должно быть не меньше нуля");
  r = _radius;
}

void Circle::SetRadius(const double val)
{
  if (val < 0)
    throw range_error("Значение радиуса должно быть не меньше нуля");
  r = val;
}

Point Circle::GetXYZPoint(const double paramValue)
{
  return Point(r * cos(paramValue), r * sin(paramValue), 0);
}

Derivative Circle::GetXYZDerivative(const double param)
{
  return Derivative(-r *sin (param), r * cos(param), 0);
}

// ------------------ Ellipse ------------------------

Ellipse::Ellipse(const double _radiusA, const double _radiusB)
{
  if (_radiusA < 0 || _radiusB < 0)
    throw range_error("Значение радиусов должно не меньше нуля");
  a = _radiusA;
  b = _radiusB;
}

void Ellipse::SetRadiusA(const double val)
{
  if (val < 0)
    throw range_error("Значение радиуса должно не меньше нуля");
  a = val;
}

void Ellipse::SetRadiusB(const double val)
{
  if (val < 0)
    throw range_error("Значение радиуса должно не меньше нуля");
  b = val;
}

Point Ellipse::GetXYZPoint(const double param)
{
  return Point(a * cos(param), b * sin(param), 0);
}

Derivative Ellipse::GetXYZDerivative(const double param)
{
  return Derivative(-a *sin (param), b * cos(param), 0);
}

// ------------------ Helix ------------------------

Helix::Helix(const double _r, const double _step)
{
  if (_r < 0)
    throw range_error("Значение радиусов должно быть не меньше нуля");
  r = _r;
  step = _step;

}

Point Helix::GetXYZPoint(const double param)
{
  return Point(r * cos(param), r * sin(param), step * param);
}

Derivative Helix::GetXYZDerivative(const double param)
{
  return Derivative(-r * sin(param), r * cos(param), step);
}

void Helix::SetRadius(const double val)
{
  if (val < 0)
    throw range_error("Значение радиусов должно быть не меньше нуля");
  r = val;
}
