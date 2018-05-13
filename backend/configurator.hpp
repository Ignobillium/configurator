#ifndef _LAYER_DESCRIPTOR_
  #include "__infrastructure/layer_descriptor.hpp"
  #define _LAYER_DESCRIPTOR_
#endif

#ifndef _VIRTUAL_LAYER_
  #include "__infrastructure/virtual_layer.hpp"
  #define _VIRTUAL_LAYER_
#endif

#ifndef _Q_GENERATION_
  #include "__infrastructure/__q_generation.hpp"
  #define _Q_GENERATION_
#endif

class configurator
{
private:
  std::vector<ld*> InputL, OutputL,BlackBox;
public:
  void regInput(std::vector<ld> iL);
    void regInput(ld *iL);
  void regOutput(std::vector<ld> oL);
    void regOutput(ld *oL);
  void regBlackBox(std::vector<ld> bB);
    void regBlackBox(ld *bB);

  void BindLayers(std::vector<ld> *Current, std::vector<ld> *Next);
    void BindLayers(ld *Current, ld *Next);
    void BindLayers(ld *Current, std::vector<ld> *Next);
    void BindLayers(std::vector<ld> *Current, ld *Next);
      inline void BindIwL(std::vector<ld> *Current);
        void BindIwL(ld* Current);
      inline void BindOwL(std::vector<ld> *Current);
        void BindOwL(ld* Current);

  std::vector<q_generation> compile();
  friend std::ostream& operator<<(std::ostream& os, const configurator& Configurator);

  configurator();
  configurator(const configurator& Configurator);
  ~configurator();
};
