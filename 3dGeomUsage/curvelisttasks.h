#ifndef CURVELISTMANAGER_H
#define CURVELISTMANAGER_H
#include <list>
#include <vector>
#include <memory>
#include <../Geom3dLib/Geom3dLib_global.h>
#include <../Geom3dLib/geom3dlib.h>

using namespace std;
using PCircle = shared_ptr<Circle>;

list<shared_ptr<Curve>> PopulateCurveList(unsigned int cnt);
void PrintPointsAndDerivs(const list<shared_ptr<Curve>> &curveList, const double param,
  const string &filename);
vector<PCircle> GetCiclesFromCurves(const list<shared_ptr<Curve>> &curveList);
void SortCircleList(vector<PCircle> &circles);
double CalcRadiusSum(const vector<PCircle> &circles);



#endif // CURVELISTMANAGER_H
