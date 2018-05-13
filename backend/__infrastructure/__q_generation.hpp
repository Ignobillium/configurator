#ifndef _VECTOR_HPP_
  #include "__vector.hpp"
  #define _VECTOR_HPP_
#endif

#ifndef _VIRTUAL_LAYER_
  #include "virtual_layer.hpp"
  #define _VIRTUAL_LAYER_
#endif

struct q_generation
{
  std::vector<vl>                  Layers;
  std::vector<std::vector<double>> Output;
  std::vector<std::vector<double>> Data;

  void calculate(std::vector<q_generation> &Queue);

  friend std::ostream& operator<<(std::ostream& os, q_generation& Qg);

  q_generation();
  q_generation(const q_generation& Qg);
  q_generation(const std::vector<vl> layers);


  ~q_generation();
};

    void q_generation::calculate(std::vector<q_generation> &Queue)
    {
      size_t i = 0;
      for(auto p = Layers.begin(); p != Layers.end(); ++p, ++i) // по каждому слою
      {
        size_t j = 0;
        for( auto q = p->Weights.begin(); q != p->Weights.end(); ++q, ++j) // по каждому входу
        {
          size_t k = 0;
          for(auto w = q->begin(); w != q->end(); ++w, ++k) // для каждого нейрона
          {
            Data[i][k] = p->Summator(  *w, Queue[ std::get<0>(p->ConfRule[j]) ].Output[  std::get<1>(p->ConfRule[j])  ] ) + p->Bias[j][k];
            Output[i][k] = p->Activator(  Data[i][k] );
          }
        }
      }
    }

        q_generation::q_generation()
        {

        }

        q_generation::q_generation(const q_generation& Qg)
        {
          Layers = Qg.Layers;
          Output = Qg.Output;
          Data = Qg.Data;
        }

        q_generation::q_generation(const std::vector<vl> layers)
        {
          Layers = layers;
          Output = std::vector<std::vector<double>>( layers.size() );
          for(size_t i = 0; i < layers.size(); ++i)
          {
            Output[i] = std::vector<double>(layers[i].Error.size());
            Data[i] = std::vector<double>(layers[i].Error.size());
          }
        }

        q_generation::~q_generation()
        {
          Layers.clear();
          Output.clear();
          Data.clear();
        }

std::ostream& operator<<(std::ostream& os, q_generation& Qg)
{
  std::cout << "\nLayers:\n" << Qg.Layers;
  std::cout << "\nOutput:\n" << Qg.Output;
  std::cout << "\nData:\n" << Qg.Data;
  return os;
}
