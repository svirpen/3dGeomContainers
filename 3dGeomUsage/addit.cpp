#include "addit.h"
#include <iomanip>
#ifdef WIN32
#include <io.h>
#endif
#include <fcntl.h>
#include <fstream>
#include <locale>

int procCoreCnt;

#ifdef WIN32
  std::basic_ostream<wchar_t> &tcout = StreamSelector<wchar_t>::stream;
#endif
#ifndef WIN32
  std::basic_ostream<char> &tcout = StreamSelector<char>::stream;
#endif


void InitForPlatform()
{
#ifdef WIN32
  _setmode(_fileno(stdout), _O_U16TEXT);
#endif
}

void InitForPlatromFile(tifstream &file)
{
#ifdef WIN32
  std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
  file.imbue(loc);
#endif
  (void)file; // чтобы скрыть предупреждение компилятора о неиспользуемом параметре
  return;
}

void InitForPlatromFile(tofstream &file)
{
#ifdef WIN32
  std::locale loc(std::locale::classic(), new std::codecvt_utf8<wchar_t>);
  file.imbue(loc);
#endif
  (void)file; // чтобы скрыть предупреждение компилятора о неиспользуемом параметре
  return;
}


tstring GetCurrentTimestamp()
{
  using namespace std::chrono;
  using clock = system_clock;

  const auto current_time_point {clock::now()};
  const auto current_time {clock::to_time_t (current_time_point)};
  tm time {*std::localtime (&current_time)};
  const auto current_time_since_epoch {current_time_point.time_since_epoch()};
  const auto current_milliseconds {duration_cast<milliseconds> (current_time_since_epoch).count() % 1000};


  tstringstream stream;
  stream << setw(2)  << setfill(_t('0')) << time.tm_hour << _t(":") << setw(2) << setfill(_t('0')) << time.tm_min
         << _t(":") << setw(2) << setfill (_t('0')) << time.tm_sec << _t(".") << setw(3) << setfill (_t('0')) << current_milliseconds;
  return stream.str();
}



tstring ConConvert(const std::string &str)
{
#ifdef WIN32
  std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
  std::wstring wide = converter.from_bytes(str.c_str());
  return wide;
#endif
  (void)str;
  return str;
}
