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

#ifndef _LAYER_DESCRIPTOR_
  #include "layer_descriptor.hpp"
  #define _LAYER_DESCRIPTOR_
#endif

#ifndef _IOSTREAM_
  #include <iostream>
  #define _IOSTREAM_
#endif

#define _v std::vector
#define _p std::pair

#define vl virtual_layer
struct virtual_layer
{
public:
  _v< _v< _v<double> > > Weights;
  _v<     _v<double>   > Bias;

  _v<        double    > Error;

  activator Activator;
  summator Summator;
  teacher Teacher;

  _v< _p<size_t/*#generationId*/, size_t/*layerId*/> > ConfRule;

  //_v<double> calculate(_v< q_generation > *Queue);

  friend std::ostream& operator<<(std::ostream& os, const vl& Vl);

  vl& operator=(const vl& Vl);

  virtual_layer();
  virtual_layer(const ld& Ld);
  virtual_layer(const vl& Vl);
  //virtual_layer(const size_t NC, const size_t IC, const activator ActFunc, const summator SummFunc, const teacher TeachFunc);

  ~virtual_layer();
};

#undef _v
#undef _p
