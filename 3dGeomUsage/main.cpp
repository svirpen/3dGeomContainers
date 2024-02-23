#include <stdio.h>
#include <iostream>
#include <string>
#include <list>
#include <memory>
#include <vector>
#include <algorithm>
#include <fcntl.h>
#include <thread>
#include <curvelisttasks.h>
#include <fstream>
#include <../Geom3dLib/Geom3dLib_global.h>
#include <../Geom3dLib/geom3dlib.h>
#include "addit.h"

void DoMainWork()
{

  try
  {
    unsigned long int n = 10000000;
//    unsigned long int n = 50000000;
//    unsigned long int n = 30;
    tcout << GetCurrentTimestamp() << _t(" ===== 1. Запуск программы =====")  << endl;
    tcout << GetCurrentTimestamp() << _t(" ===== 2. Генерация списка с кривыми =====") << endl;
    list<shared_ptr<Curve>> curves = PopulateCurveList(n);
    tcout << GetCurrentTimestamp()
         << _t(" ===== 3. Расчет точек и производных, запись в файл  ===="  << endl);
    PrintPointsAndDerivs(curves, (M_PI / 4), "out.txt");
    tcout << GetCurrentTimestamp() << _t(" ===== 4. Извлечение окружностей из списка =====") << endl;

    vector<shared_ptr<Circle>> circles = GetCiclesFromCurves(curves);

    tcout << GetCurrentTimestamp() << _t(" ===== 5. Сортировка окружностей по радиусу =====") << endl;
    SortCircleList(circles);
    tcout << GetCurrentTimestamp()
         << _t(" ===== 6. Расчет суммы радиусов с использованием OpenMP =====") << endl;
    double sum = CalcRadiusSum(circles);
    tcout << GetCurrentTimestamp()
         << _t(" ===== 6. Сумма равна ") << sum << _t(" =====") << endl;
    tcout << GetCurrentTimestamp() << _t(" ===== Завершение работы =====")  << endl;

  }
  catch (exception& e)
  {
    tcout << _t("Произошла ошибка. ") << ConConvert(e.what()) << endl;
  }


}

int main()
{
  InitForPlatform();

  procCoreCnt = thread::hardware_concurrency();
  DoMainWork();
  tcout << _t("Готово. Нажмите Enter, чтобы выйти")  << endl;
  string s;
  std::getline(std::cin, s);
  return 0;


}
