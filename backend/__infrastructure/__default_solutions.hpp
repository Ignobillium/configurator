#ifndef _TDEFS_
  #include "__t-defs.hpp"
  #define _TDEFS_
#endif

#ifndef _MATH_
  #include <math.h>
  #define _MATH_
#endif


namespace _default
{
  inline double Linear(double x)
  {
    return x;
  }

  inline double Quad(double x)
  {
    return x*x;
  }

  inline double Sigma(double x)
  {
    return 1. / ( 1 + exp(-x) );
  }

  const activator Activator = &Sigma;

  inline double Summ(std::vector<double> Weights, std::vector<double> Input)
  {
    double Res = 0;
    for(int i = 0; i < Input.size(); ++i)
      Res += Input[i] * Weights[i];
    return Res;
  }

  inline double QuadSumm(std::vector<double> Weights, std::vector<double> Input)
  {
    double Res = 0;
    for(int i = 0; i < Input.size(); ++i)
      Res += Input[i] * Weights[i] * Weights[i];
    return Res;
  }

  const summator Summator = &Summ;

  double Alpha = 0.05;
  double Accuracy = 0.0001;

  inline double Grad(double Input, double TotalOutput, double Error, activator ActFunc)
  {
    return Alpha * Error * Input * ( ActFunc(TotalOutput + Accuracy) - ActFunc(TotalOutput) ) / Accuracy;
  }

  const teacher Teacher = &Grad;
}
