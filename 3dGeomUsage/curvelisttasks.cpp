#include "curvelisttasks.h"
#include <random>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <typeinfo>

#include "addit.h"
#include <omp.h>

using namespace std;

list<shared_ptr<Curve>> PopulateCurveList(unsigned int cnt)
{
  list<shared_ptr<Curve>> curveList;
  default_random_engine rndeng {static_cast<long unsigned int>(time(0))};
//  default_random_engine rndeng {static_cast<long unsigned int>((0))};
  uniform_int_distribution dis04(0, 2);
  uniform_real_distribution dis01_100(0.1, 100.0);
  for (unsigned int i = 0; i < cnt; i++)
  {
    int curveType = dis04(rndeng);
    switch (curveType)
    {
    case 0:
      curveList.push_back(make_shared<Circle>(Circle{dis01_100(rndeng)}));
      break;
    case 1:
      curveList.push_back(make_shared<Ellipse>(Ellipse{dis01_100(rndeng), dis01_100(rndeng)}));
      break;
    case 2:
      curveList.push_back(make_shared<Helix>(Helix{dis01_100(rndeng), dis01_100(rndeng)}));
    default:
      break;
    }
  }
  return curveList;
}


void PrintPointsAndDerivs(const list<shared_ptr<Curve>> &curveList, const double param,
  const string &filename)
{

  tofstream file;
  if (filename != "")
    file.open(filename, ios::trunc );

  InitForPlatromFile(file);

  tstringstream ss, ss1;
  for (shared_ptr element: curveList)
  {

    ss.str(tstring()); ss1.str(tstring());
    omp_set_num_threads(procCoreCnt > 1 ? 2 : 1 );

    #pragma omp parallel sections
    {
       #pragma omp section
       {
         ss << _t("Point") << element->GetXYZPoint(param);
       }
       #pragma omp section
       {
        ss1 << _t(", Deriv:") << element->GetXYZDerivative(param) << "\n";
       }
    }
//    continue;
    if (filename == "")
       tcout << ss.str() << ss1.str();
    else
      file << ss.str() <<  ss1.str();

  }
}

vector<PCircle> GetCiclesFromCurves(const list<shared_ptr<Curve>> &curveList)
{
  vector<PCircle> circles;
  circles.reserve(curveList.size());
  for (auto curve: curveList)
//    if (typeid(*curve).hash_code() == typeid(Circle).hash_code())
      if (dynamic_cast<Circle*>(curve.get()) != 0)
        circles.push_back(dynamic_pointer_cast<Circle>(curve));
  return circles;
}

void SortCircleList(vector<PCircle> &circles)
{
  sort(circles.begin(), circles.end(),[]( const PCircle &circle1, const PCircle &circle2)
  {
    double prev = circle1->GetRadius();
    double cur = circle2->GetRadius();
    if (abs(prev - cur) < numeric_limits<double>::epsilon())
      return false;
    return (prev < cur) ;
  });
}

double CalcRadiusSum(const vector<PCircle> &circles)
{
  omp_set_num_threads(procCoreCnt);

  int n = circles.size();
  double sum = 0;
  {
    #pragma omp parallel for reduction (+:sum)
    for (int i = 0; i < n; i++)
      sum += circles[i]->GetRadius();
  }

  return sum;
}


