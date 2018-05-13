#ifndef _TDEFS_
  #include "__t-defs.hpp"
  #define _TDEFS_
#endif

#ifndef _VECTOR_HPP_
  #include "__vector.hpp"
  #define _VECTOR_HPP_
#endif

#ifndef _PAIR_HPP_
  #include "__pair.hpp"
  #define _PAIR_HPP_
#endif

#ifndef _DEFAULT_SOLUTIONS_
  #include "__default_solutions.hpp"
  #define _DEFAULT_SOLUTIONS_
#endif

#ifndef _IOSTREAM_
  #include <iostream>
  #define _IOSTREAM_
#endif

#define ld layer_descriptor

struct layer_descriptor
{
  size_t NeuronsCount;
  size_t InputsCount;

  activator Activator;
  summator Summator;
  teacher Teacher;

  std::vector<ld*> Prev;

  size_t PrevsCount;
  size_t IdQ;
  bool Visited;

  friend std::ostream& operator<<(std::ostream& os, const ld& Ld);
  //friend std::istream& operator>>(std::istream& is,       ld& Ld);

  ld& operator=(const ld& Ld);

  //explicit layer_descriptor() ;
  layer_descriptor(const ld& Ld);
  layer_descriptor(const size_t NC, const size_t IC, const activator ActFunc, const summator SummFunc, const teacher TeachFunc);

  ~layer_descriptor();
};
