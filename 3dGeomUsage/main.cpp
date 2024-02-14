#include <stdio.h>
#include <iostream>
#include <string>
#include <list>
#include <memory>
#include <omp.h>
#include <vector>
#include <algorithm>
#include <thread>
#include <curvelisttasks.h>
#include <../Geom3dLib/Geom3dLib_global.h>
#include <../Geom3dLib/geom3dlib.h>
#include "addit.h"

void DoMainWork()
{

  try
  {
    unsigned long int n = 1000000;
//    unsigned long int n = 50000000;
//    unsigned long int n = 30;
    cout << GetCurrentTimestamp() << " ===== 1. Запуск программы ====="  << endl;
    cout << GetCurrentTimestamp() << " ===== 2. Генерация списка с кривыми =====" << endl;
    list<shared_ptr<Curve>> curves = PopulateCurveList(n);
    cout << GetCurrentTimestamp()
         << " ===== 3. Расчет точек и производных, запись в файл  ===="  << endl;
    PrintPointsAndDerivs(curves, (M_PI / 4), "out.txt");
    cout << GetCurrentTimestamp() << " ===== 4. Извлечение окружностей из списка =====" << endl;

    vector<shared_ptr<Circle>> circles = GetCiclesFromCurves(curves);

    cout << GetCurrentTimestamp() << " ===== 5. Сортировка окружностей по радиусу =====" << endl;
    SortCircleList(circles);
    cout << GetCurrentTimestamp()
         << " ===== 6. Расчет суммы радиусов с использованием OpenMP =====" << endl;
    double sum = CalcRadiusSum(circles);
    cout << GetCurrentTimestamp()
         << " ===== 6. Сумма равна " << sum << " =====" << endl;
    cout << GetCurrentTimestamp() << " ===== Завершение работы ====="  << endl;

  }
  catch (exception& e)
  {
    cout << "Произошла ошибка. " << e.what() << endl;
  }

cout << GetCurrentTimestamp() << " ======= Готово ======"  << endl;

}

int main()
{

  procCoreCnt = thread::hardware_concurrency();
  DoMainWork();
  cout << "Готово. Нажмите Enter, чтобы выйти" << endl;
  string s;
  std::getline(std::cin, s);
  return 0;


}
