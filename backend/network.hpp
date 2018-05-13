#ifndef _CONFIGURATOR_
  #include "configurator.hpp"
  #define _CONFIGURATOR_
#endif

#ifndef _VECTOR_HPP_
  #include "__infrastructure/__vector.hpp"
  #define _VECTOR_HPP_
#endif

#ifndef _Q_GENERATION_
  #include "__infrastructure/__q_generation.hpp"
  #define _Q_GENERATION_
#endif

struct network
{
  std::vector<q_generation> Queue;
  std::vector<std::vector<double>> Expectation;

  inline double accuracy();

  inline std::vector<std::vector<double>> GetRes();

  inline void loadData(std::istream& DataStream);
  inline void loadData(std::ifstream& DataStream);

  inline void loadExp(std::istream& ExpStream);
  inline void loadExp(std::ifstream& ExpStream);

  inline void compute();
  inline void broadcastError();

  //void calculateError(vl *Current, vl *Next, size_t Channel);
  void broadcastError(vl &Source);

  void corrWeights();
  inline void teach(bool exitCondition, std::istream& DataStream, std::istream& ExpStream, std::ostream& Output);
  inline void teach(size_t iterationsCount, std::istream& DataStream, std::istream& ExpStream, std::ostream& Output);
  inline void teach(size_t iterationsCount, std::ifstream& DataStream, std::ifstream& ExpStream, std::ofstream& Output);

  void work(bool exitCondition, std::istream& DataStream, std::ostream& Output);
  void work(size_t iterationsCount, std::istream& DataStream, std::ostream& Output);

  inline void uploadData(std::ostream& Output);
  inline void uploadData(std::ofstream& Output);

  inline void save(std::ostream& Output);
  inline void save(std::ofstream& Output);

  network(const std::vector<q_generation> queue);
  network(configurator& Configurator);

  ~network();
};
