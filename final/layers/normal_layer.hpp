#ifndef _NORMAL_LAYER_
  #define _NORMAL_LAYER_

  namespace configurator
  {
    namespace layers
    {
      class normal_layer: public virtual_layer
      {
        friend configurator::adaptation::teacher;
      public:
        boost::numeric::ublas::vector<double>& calculateOutput() noexcept;
        void teach() noexcept;

         normal_layer() noexcept;
        ~normal_layer() noexcept;

        normal_layer(const normal_layer& Other) noexcept;

        normal_layer(const layer_descriptor<normal_layer>& Ld) noexcept;

        normal_layer& operator= (const normal_layer& Other) noexcept;
      };
    }
  }

#endif
