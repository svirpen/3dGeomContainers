#ifndef GEOM3DLIB_H
#define GEOM3DLIB_H

#include <cmath>
#include <iostream>
#include <string>
#include <stdarg.h>
#include <math.h>
#include <omp.h>
#include "Geom3dLib_global.h"

extern bool isDebug;
using namespace std;

enum CurveType {ctAll = 0, ctCircle, ctEllipse, ctHelix};

struct GEOM3DLIB_EXPORT Point
{
  double x, y, z;
  Point() : x{0}, y{0}, z{0} {}
  Point(const double _x, const double _y,const double _z) : x{_x}, y{_y}, z{_z} {}
  string ToStr() {return "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z);}
  friend std::ostream &operator<<(std::ostream &stream,  const Point& point)  {
     return stream << "(" << point.x << ", " << point.y << ", " << point.z << ")"; }
};

struct GEOM3DLIB_EXPORT Derivative
{
  double x, y, z;
  Derivative() : x{0}, y{0}, z{0} {}
  Derivative(const double _x, const double _y, const double _z) { x = _x; y = _y; z = _z;}
  string ToStr() {return "(" + to_string(x) + ", " + to_string(y) + ", " + to_string(z);}
  friend std::ostream &operator<<(std::ostream &stream,  const Derivative& dvt) {
     return stream << "(" << dvt.x << ", " << dvt.y << ", " << dvt.z << ")"; }

};

class GEOM3DLIB_EXPORT Curve
{
  int baza;
public:
   Curve() {  }

   virtual ~Curve() { }

   virtual Point GetXYZPoint(const double paramValue) = 0;
   virtual Derivative GetXYZDerivative(const double paramValue) = 0;

};

class GEOM3DLIB_EXPORT Circle : public Curve
{
private:
  double r;
public:
  Circle() : r{0.1} {}
  Circle(const double _radius);
  ~Circle() override { }

  Point GetXYZPoint(const double param)  override;
  Derivative GetXYZDerivative(const double param) override;

  double GetRadius() {return r;}
  void SetRadius(const double val);

};

class GEOM3DLIB_EXPORT Ellipse : public Curve
{
private:
  double a, b;
public:
  Ellipse() : a{0.1}, b{0.1} {}
  Ellipse(const double _radiusA, const double _radiusB);
  ~Ellipse() {}

  Point GetXYZPoint(const double param) override;
  Derivative GetXYZDerivative(const double param) override;

  double GetRadiusA() {return a;}
  double GetRadiusB() {return b;}
  void SetRadiusA(const double val);
  void SetRadiusB(const double val);

};

class GEOM3DLIB_EXPORT Helix : public Curve
{
private:
  double r, step;
public:
  Helix() : r{0.1}, step{0.1} {}
  Helix(const double _r, const double _step);
  ~Helix() {}

  Point GetXYZPoint(const double param)  override;
  Derivative GetXYZDerivative(const double param) override;

  double GetRadius() {return r;}
  double GetStep() {return step;}
  void SetRadius(const double val);
  void SetStep(const double val) {step = val;}

};


#endif // GEOM3DLIB_H
