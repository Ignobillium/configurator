#ifndef _VIRTUAL_LAYER_
  #define _VIRTUAL_LAYER_

  namespace configurator
  {
    namespace layers
    {
      class virtual_layer
      {
        // friend configurator::adaptation::teacher;
      protected:
        boost::numeric::ublas::matrix<double> *Weights;

        boost::numeric::ublas::vector<double>  Bias;
        boost::numeric::ublas::vector<double>  Error;

        boost::numeric::ublas::vector<double> Output;
        boost::numeric::ublas::vector<double> ActivatedOutput; // в идеале избавиться от этого поля

        configurator::adaptation::activator *Activator;
        configurator::adaptation::teacher  *Teacher;

        unsigned long  PrevLayersCount;
        virtual_layer* PrevLayers;
      public:
        virtual boost::numeric::ublas::vector<double>& calculateOutput() noexcept = 0;
        virtual void teach() noexcept = 0;

                 virtual_layer() noexcept {}
        virtual ~virtual_layer() noexcept {}
               //virtual_layer(const layer_descriptor<virtual_layer>& Ld) noexcept;
      };
    }
  }

#endif
