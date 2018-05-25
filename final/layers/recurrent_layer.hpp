#ifndef _RECURRENT_LAYER_
  #define _RECURRENT_LAYER_

  namespace configurator
  {
    namespace layers
    {
      class recurrent_layer: public virtual_layer
      {
        friend configurator::adaptation::teacher;
      public:
        boost::numeric::ublas::vector<double>& calculateOutput() noexcept;
        void teach() noexcept;

         recurrent_layer() noexcept;
        ~recurrent_layer() noexcept;

        recurrent_layer(const recurrent_layer& Other) noexcept;

        recurrent_layer(const layer_descriptor<recurrent_layer>& Ld) noexcept;

        recurrent_layer& operator= (const recurrent_layer& Other) noexcept;
      };
    }
  }

#endif
