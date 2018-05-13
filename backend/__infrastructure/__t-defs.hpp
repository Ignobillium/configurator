#ifndef _VECTOR_HPP_
  #include "__vector.hpp"
  #define _VECTOR_HPP_
#endif

using size_t = long unsigned int;

using activator = double(*)(double x);
using summator  = double(*)(std::vector<double> Weights, std::vector<double> Data);

using teacher = double(*)(double Input, double TotalOutput, double Error, activator ActFunc);
