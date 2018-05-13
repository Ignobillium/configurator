vl::virtual_layer()
{
  Weights = _v<_v<_v<double>>>(1);
  Weights[0] = _v<_v<double>>(1);
  Weights[0][0] = _v<double>(1);
  Weights[0][0][0] = 0.5;

  Bias = _v<_v<double>>(1);
  Bias[0] = _v<double>(1);
  Bias[0][0] = 0.25;

  Error = _v<double>(1);
  Error[0] = 0;
}

#ifndef _TIME_
  #include <time.h>
  #define _TIME_
#endif

vl::virtual_layer(const ld& Ld)
{
  if(!Ld.Prev.empty())
  {
    ///
    ///
    /// ПРОВЕРКА НА ПУСТОТУ PREVS!!!!!
    /// пустой вектор предыдущих <=> входной слой
    ///
    ///
    //std::cout << "\nstart creating vl(ld&);\n";
    srand(time(NULL));
    //std::cout << "\nLd.Ic = " << Ld.InputsCount;
    Weights = _v<_v<_v<double>>>(Ld.InputsCount);
    //std::cout << "\nWeights created!\nstart creating Bias;";
    Bias    = _v<    _v<double>>(Ld.InputsCount);
    //std::cout << "\nbias created! start creating error";
    Error   = _v<      double  >(Ld.NeuronsCount);
    //std::cout <<"\nError created!";

    ConfRule = _v< _p<size_t, size_t> >(Ld.InputsCount);

    for(size_t i = 0; i < Ld.InputsCount; ++i)
    {
      Weights[i] = _v<_v<double>>(Ld.NeuronsCount);
      Bias[i]    =    _v<double>(Ld.NeuronsCount);
      for(size_t j = 0; j < Ld.NeuronsCount; ++j)
      {
        Bias[i][j]  = 1.*rand()/RAND_MAX;
        Error[j]    = 0;

        Weights[i][j] = _v<double>(Ld.Prev[i]->NeuronsCount);
        for(size_t k = 0; k < Ld.Prev[i]->NeuronsCount; ++k)
          Weights[i][j][k] = 1.*rand()/RAND_MAX;
      }

        ConfRule[i] = std::make_pair( Ld.Prev[i]->PrevsCount, Ld.Prev[i]->IdQ );
    }

    Activator = Ld.Activator;
    Summator = Ld.Summator;
    Teacher = Ld.Teacher;
  }
  else
  {
    Error   = _v<double>(Ld.NeuronsCount);

    Activator = Ld.Activator;
    Summator = Ld.Summator;
    Teacher = Ld.Teacher;
  }
}

vl::virtual_layer(const vl& Vl)
{
  Weights = Vl.Weights;
  Bias    = Vl.Bias;
  Error   = Vl.Error;

  ConfRule = Vl.ConfRule;

  Activator = Vl.Activator;
  Summator = Vl.Summator;
  Teacher = Vl.Teacher;
}

/*
#ifndef _DEFAULT_SOLUTIONS_
  #include "__default_solutions.hpp"
  #define _DEFAULT_SOLUTIONS_
#endif
vl::virtual_layer(const size_t NC, const size_t IC, const activator ActFunc = _default::Activator, const summator SummFunc = _default::Summator, const teacher TeachFunc = _default::Teacher)
{
  srand(time(NULL));

  Weights = _v<_v<double>>(IC);
  Bias    = _v<   double >(IC);
  Error   = _v<   double >(IC);

  //ConfRule = _v< _p<size_t, size_t> >(Ld.InputsCount);

  for(size_t i = 0; i < IC; ++i)
  {
      Weights[i] = _v<double>(Ld.Prev[i]->NeuronsCount);
      for(size_t j = 0; j < Ld.Prev[i]->NeuronsCount; ++j)
        Weights[i][j] = 1.*rand()/RAND_MAX;

      Bias[i]  = 1.*rand()/RAND_MAX;
      Error[i] = 0;

  }

  Activator = ActFunc;
  Summator = SummFunc;
  Teacher = TeachFunc;
}
*/

vl::~virtual_layer()
{
  Weights.clear();
  Bias.clear();
  Error.clear();
  ConfRule.clear();
}
