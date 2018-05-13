#ifndef _VECTOR_
  #define _VECTOR_
  #include <vector>
#endif

#ifndef _IOSTREAM_
  #include <iostream>
  #define _IOSTREAM_
#endif

#ifndef _FSTREAM_
  #include <fstream>
  #define _FSTREAM_
#endif

#ifndef _ALGORITHM_
  #include <algorithm>
  #define _ALGORITHM_
#endif

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T> Vector)
{
  typename std::vector<T>::const_iterator it;
  for(it = Vector.begin(); it != Vector.end(); ++it)
    os << *it << ' ';
  return os;
}

template<typename T>
std::ofstream& operator<<(std::ofstream& os, const std::vector<T> Vector)
{
  typename std::vector<T>::const_iterator it;
  for(it = Vector.begin(); it != Vector.end(); ++it)
    os << *it << ' ';
  return os;
}


#define _MAX(a, b) ( ((a)>(b))*(a)  +  ((a)<(b))*(b) )
#define _MIN(a, b) ( ((a)>(b))*(b)  +  ((a)<(b))*(a) )

template<typename T>
std::vector<T> operator+(std::vector<T> V1, std::vector<T> V2)
{
  std::vector<T> Res;

  size_t a = V1.size(), b = V2.size(), x = _MAX(a, b), n = _MIN(a, b);

  Res = std::vector<T>(x);
  for(size_t i = 0; i < n; ++i)
    Res[i] = V1[i] + V2[i];

  if( a > b )
    for(size_t i = n; i < x; ++i) Res[i] = V1[i];
  else
    for(size_t i = n; i < x; ++i) Res[i] = V2[i];

  return Res;
}

#undef _MAX
#undef _MIN

// "isInside"
template<typename T>
bool operator<<(const std::vector<T> &Vector, T &Elem)
{
  bool Res = false;
  for(typename std::vector<T>::const_iterator p = Vector.begin(); p != Vector.end(); ++p)
    Res = Res || (*p == Elem);
  return Res;
}

template<typename T>
bool operator>>(T &Elem, const std::vector<T> &Vector)
{
  bool Res = false;
  for(typename std::vector<T>::const_iterator p = Vector.begin(); p != Vector.end(); ++p)
    Res = Res || (*p == Elem);
  return Res;
}
