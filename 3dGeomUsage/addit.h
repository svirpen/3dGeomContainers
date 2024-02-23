#ifndef ADDIT_H
#define ADDIT_H

#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <sstream>
#include <string>
#include <codecvt>
#include <locale>

using namespace std;



#ifdef WIN32
#define _t(x) L##x
#endif
#ifndef WIN32
#define _t(x) x
#endif

extern int procCoreCnt;

template <typename T_Char>
struct StreamSelector;

template <>
struct StreamSelector<char>
{
   static constexpr std::ostream &stream = std::cout;
};

template <>
struct StreamSelector<wchar_t>
{
   static constexpr std::wostream &stream = std::wcout;
};


#ifdef WIN32
  extern std::basic_ostream<wchar_t> &tcout;
  using tstring = wstring;
  using tstringstream = wstringstream;
  using tifstream = wifstream;
  using tofstream = wofstream;
#endif
#ifndef WIN32
  extern std::basic_ostream<char> &tcout;
  using tstring = string;
  using tstringstream = stringstream;
  using tifstream = ifstream;
  using tofstream = ofstream;
#endif

void InitForPlatform();
void InitForPlatromFile(tifstream &file);
void InitForPlatromFile(tofstream &file);
tstring ConConvert(const std::string &str);
tstring GetCurrentTimestamp();

#endif // ADDIT_H
