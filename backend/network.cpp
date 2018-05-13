#include "configurator.cpp"

#ifndef _NETWORK_
  #include "network.hpp"
  #define _NETWORK_
#endif

#ifndef _MATH_
  #include <math.h>
  #define _MATH_
#endif

inline std::vector<std::vector<double>> network::GetRes()
{
  return  Queue.back().Output;
}

#define _MAX(a, b) ( ((a)>(b))*(a)  +  ((a)<(b))*(b) )
inline double network::accuracy()
{
  auto p = GetRes();
  double Accuracy = p[0][0];
  //std:: cout << "\nAccuracy :" << Accuracy << "\n\t p = " << p ;//<< "\n next one;";
  //std::cout << "\n p = " << p << "\n";
  //std::cout << "\nauto j...";
  size_t q = 0;
  for(auto j = p.begin(); j != p.end(); ++j, ++q)
  {
    size_t w = 0;
    //std::cout << "\n\t p[" << q << "] = " << *j << " ";
    for(auto k = j->begin(); k != j->end(); ++k, ++w)
      Accuracy = _MAX(Accuracy, *k - Expectation[q][w]);
  }
  /*
  for(size_t j = 0; j < p.size(); ++j)
  {
    std::cout << "\n\t p[" << q << "] = " << *j << " ";
    for(auto k = 0; k < p[j].size(); k)
      Accuracy = _MAX(Accuracy, *k - Expectation[q][w]);
  }
  */
  //std::cout << "\nAccuracy = " << Accuracy;
  return Accuracy;
}
#undef _MAX

inline void network::loadData(std::istream& DataStream)
{
  //std::cout << "\nEnter data You wish to process $ ";
  size_t i = 0;
  for(auto p = Queue[0].Output.begin(); p != Queue[0].Output.end(); ++p, ++i)
  {
    size_t k = 0;
    for(auto  j = p->begin(); j != p->end(); ++j, ++k)
    {
      DataStream >> *j;
      //std::cout << "\nLoaded " << *j << " to Output[" << i << "][" << k << "];\n";
    }
  }
}

inline void network::loadData(std::ifstream& DataStream)
{
  //std::cout << "\nEnter data You wish to process $ ";
  size_t i = 0;
  for(auto p = Queue[0].Output.begin(); p != Queue[0].Output.end(); ++p, ++i)
  {
    size_t k = 0;
    for(auto  j = p->begin(); j != p->end(); ++j, ++k)
    {
      DataStream >> *j;
      //std::cout << "\nLoaded " << *j << " to Output[" << i << "][" << k << "];\n";
    }
  }
}

inline void network::loadExp(std::istream& ExpStream)
{
  //std::cout << "\nEnter your expectation $ ";
  size_t i = 0;
  for(auto p = Expectation.begin(); p != Expectation.end(); ++p, ++i)
  {
    size_t k = 0;
    for(auto  j = p->begin(); j != p->end(); ++j, ++k)
    {
      ExpStream >> *j;
      //std::cout << "\nLoaded " << *j << " to Expectation[" << i << "][" << k << "];\n";
    }
  }
}

inline void network::loadExp(std::ifstream& ExpStream)
{
  //std::cout << "\nEnter your expectation $ ";
  size_t i = 0;
  for(auto p = Expectation.begin(); p != Expectation.end(); ++p, ++i)
  {
    size_t k = 0;
    for(auto  j = p->begin(); j != p->end(); ++j, ++k)
    {
      ExpStream >> *j;
      //std::cout << "\nLoaded " << *j << " to Expectation[" << i << "][" << k << "];\n";
    }
  }
}

inline void network::uploadData(std::ostream& Output)
{
  Output << GetRes() << '\n';
}

inline void network::uploadData(std::ofstream& Output)
{
  Output << GetRes() << '\n';
}

inline void network::save(std::ostream& Output)
{
  for(auto p = Queue.begin(); p != Queue.end(); ++p)
    for(auto j = p->Layers.begin(); j != p->Layers.end(); ++j)
      for(auto k = j->Weights.begin(); k != j->Weights.end(); ++k)
        Output << *k;
}

inline void network::save(std::ofstream& Output)
{
  for(auto p = Queue.begin(); p != Queue.end(); ++p)
    for(auto j = p->Layers.begin(); j != p->Layers.end(); ++j)
      for(auto k = j->Weights.begin(); k != j->Weights.end(); ++k)
        Output << *k;
}

inline void network::compute()
{
  size_t k = 1;
  for(auto p = (Queue.begin() + 1); p!=Queue.end(); ++p, ++k)
  {
    //std::cout << "\nProcessing generation[" << k << "]\n";
    p->calculate(Queue);
  }
}

void network::broadcastError(vl &Source)
{
  size_t Channel = 0;
  for(auto p = Source.ConfRule.begin(); p != Source.ConfRule.end(); ++p, ++Channel)
  {
    size_t i = 0;
    for(auto q = Queue[p->first].Layers[p->second].Error.begin(); q != Queue[p->first].Layers[p->second].Error.end(); ++q, ++i)
    {
      size_t j = 0;
      for(auto e = Source.Error.begin(); e != Source.Error.end(); ++e, ++j)
        *q += (*e) * Source.Weights[Channel][j][i];
    }
    if(   !Queue[p->first].Layers[p->second].ConfRule.empty()   )
      broadcastError( Queue[p->first].Layers[p->second] );
  }
}

void network::broadcastError()
{
  //std::cout << "\n Set errors to 0";
  for(auto p = Queue.begin(); p != Queue.end(); ++p)
    for(auto j = p->Layers.begin(); j != p->Layers.end(); ++j)
      for(auto k = j->Error.begin(); k != j->Error.end(); ++k)
        *k = 0;
  //std::cout << "\n done";

  //std::cout << "\n Calculate explicit error";
  size_t lr = 0;
  for(auto p = Queue.back().Layers.begin(); p != Queue.back().Layers.end(); ++p, ++lr)
  {
     size_t cur = 0;
     for(auto k = p->Error.begin(); k != p->Error.end(); ++k, ++cur)
     {
      *k = Expectation[lr][cur] - Queue.back().Output[lr][cur];
      //std::cout << "\n\t Error[lastGen][layer " << lr << "][neuron " << cur << "] = " << *k;
    }
  }

  //std::cout << "\n Broadcasting error";
  for(auto p = Queue.back().Layers.begin(); p != Queue.back().Layers.end(); ++p)
    broadcastError(*p);
  //std::cout << "\n Error have been broadcasted";
}

void network::corrWeights()
{
  //std::cout << "\nStart weights correcting";
  size_t generation = 0;
  for(auto p = Queue.begin() + 1; p != Queue.end(); ++p, ++generation) // every generation
  {
    //std::cout <<"\nGeneration #" << generation;
    size_t layer = 0;
    for(auto j = p->Layers.begin(); j != p->Layers.end(); ++j, ++layer) // every layer in generation
    {
      //std::cout << "\n\tLayer #" << layer;
      size_t kId = 0;
      for(auto k = j->Weights.begin(); k != j->Weights.end(); ++k, ++kId) // every channel
      {
        //std::cout << "\n\t\tChannel #" << kId;
        size_t nId = 0;
        for(auto l = k->begin(); l != k->end(); ++l, ++nId) // every neuron
        {
          //std::cout << "\n\t\t\tNeuron #" << nId << "\n\t\t\tlinks ";
          size_t lId = 0;
          for(auto m = l->begin(); m != l->end(); ++m, ++lId) // every link
          {
            //Input = Queue[ std::get<0>(j->ConfRule[kId])  ].Output[  std::get<1>(j->ConfRule[kId])  ][nId]; <- nId == нейрон текущего слоя, а не предыдущего, блять. Отсюда ошибка сегментации
                                                                                                      // тут должно быть lId: Id связи, которая соединяет этот нейрон с тем выходным значением
            //TotalOutput = p->Output[nId][lId]; <- а здесь неправильные индексы. 1й must be = id текущего слоя, 2й must be id текущего нейрона!
                                                                                          // итого: id1 = layer, id2 = nId
            //Error = j->Error[nId]; // в этих двух строчках всё правильно
            //ActFunc = j->Activator;
            double corW = j->Teacher( Queue[ std::get<0>(j->ConfRule[kId])  ].Output[  std::get<1>(j->ConfRule[kId])  ][lId], p->Data[layer][nId], j->Error[nId], j->Activator);
            //std::cout << "\n\nCorW = " << corW << "\n";
            *m += corW;
            //std::cout << " " << lId;
          }
          double corBias = j->Teacher( Queue[ std::get<0>(j->ConfRule[kId])  ].Output[  std::get<1>(j->ConfRule[kId])  ][lId], 1, j->Error[nId], j->Activator);
          std::cout << "\nError = " << j->Error[nId];
          std::cout << "\nCorBias = " << corBias;
          //std::cout << "\nBias old = " << j->Bias[kId][nId];
          j->Bias[kId][nId] += corBias;
          //std::cout << "\nBias new = " << j->Bias[kId][nId];
          //std::cout << " corrected\n";
        }
      }
    }
  }

}

inline void network::teach(bool exitCondition, std::istream& DataStream, std::istream& ExpStream, std::ostream& Output)
{
  while(!exitCondition)
  {
    loadData(DataStream);
    compute();
    loadExp(ExpStream);
    broadcastError();
    corrWeights();
  }
  save(Output);
}

void network::teach(size_t iterationsCount, std::istream& DataStream, std::istream& ExpStream, std::ostream& Output)
{
  for(size_t i = 0; i < iterationsCount + 1; ++i)
  {
    loadData(DataStream);
    compute();
    loadExp(ExpStream);
    broadcastError();
    corrWeights();
  }
  save(Output);
}

void network::teach(size_t iterationsCount, std::ifstream& DataStream, std::ifstream& ExpStream, std::ofstream& Output)
{
  for(size_t i = 0; i < iterationsCount + 1; ++i)
  {
    loadData(DataStream);
    compute();
    loadExp(ExpStream);
    broadcastError();
    corrWeights();
    Output << "Iteration " << i << ";\n\t Accuracy = " << accuracy() << "\n\t Input = (" << Queue[0].Output << ")\n\tOutput = " << GetRes() << '\n';// << "\nBias last= " << Queue.back().Layers.back().Bias << "\n";
  }
  //save(Output);
}

void network::work(bool exitCondition, std::istream& DataStream, std::ostream& Output)
{
  while(!exitCondition)
  {
    loadData(DataStream);
    compute();
    uploadData(Output);
  }
}

void network::work(size_t iterationsCount, std::istream& DataStream, std::ostream& Output)
{
  for(size_t i = 0; i < iterationsCount + 1; ++i)
  {
    loadData(DataStream);
    compute();
    uploadData(Output);
  }
}

network::network(const std::vector<q_generation> queue)
{
  Queue = queue;

  Expectation = std::vector<std::vector<double>>( Queue.back().Layers.size() );
  size_t i =0;
  for(auto p = Queue.back().Layers.begin(); p != Queue.back().Layers.end(); ++p, ++i)
    Expectation[i] = std::vector<double>( p->Error.size() );
}

network::network(configurator& Configurator)
{
  Queue = Configurator.compile();

  Expectation = std::vector<std::vector<double>>( Queue.back().Layers.size() );
  size_t i = 0;
  for(auto p = Queue.back().Layers.begin(); p != Queue.back().Layers.end(); ++p, ++i)
    Expectation[i] = std::vector<double>( p->Error.size() );
}

network::~network()
{
  Queue.clear();
  Expectation.clear();
}
