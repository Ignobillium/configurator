#ifndef _UTILITY_
  #include <utility>
  #define _UTILITY_
#endif

#ifndef _IOSTREAM_
  #include <iostream>
  #define _IOSTREAM_
#endif

#ifndef _FSTREAM_
  #include <fstream>
  #define _FSTREAM_
#endif

template<typename T1, typename T2>
std::ostream& operator<< (std::ostream &os, std::pair<T1, T2> a)
{
  //os << a.first << ' ' << a.second;
  os << '(' << std::get<0>(a) << ',' << std::get<1>(a) << ") ";
  return os;
}

template<typename T1, typename T2>
std::ofstream& operator<< (std::ofstream &os, std::pair<T1, T2> a)
{
  //os << a.first << ' ' << a.second;
  os << '(' << std::get<0>(a) << ',' << std::get<1>(a) << ") ";
  return os;
}
