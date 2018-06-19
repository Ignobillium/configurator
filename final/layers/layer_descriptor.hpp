#ifndef _LAYER_DESCRIPTOR_
  #define _LAYER_DESCRIPTOR_

  namespace configurator
  {
    namespace layers
    {
      class ld_core
      {
      protected:
        size_t NeuronsCount;
        size_t InputsCount;

        configurator::adaptation::activator *Activator; // TODO: заменить смарт поинтером !!!
        configurator::adaptation::teacher   *Teacher;   // TODO: заменить смарт поинтером !!!

        std::vector<ld_core*> PrevLayers;

        size_t GenerationId;
        bool   IsVisited;
      public:
        virtual virtual_layer* construct() = 0 const noexcept;

                 ld_core() noexcept {}
        virtual ~ld_core() noexcept {}
      };

      template<typename layer_type>
      class layer_descriptor: public ld_core
      {
      public:
        virtual_layer* construct()      const noexcept; // возможно есть резон заменить на ссылки
        layer_type*    constructLayer() const noexcept; // возможно есть резон заменить на ссылки

         layer_descriptor() noexcept;
        ~layer_descriptor() noexcept;

        layer_descriptor(const layer_descriptor<layer_type>& Ld) noexcept;
        layer_descriptor(const size_t NC,
                         const configurator::adaptation::activator *ActF,
                         const configurator::adaptation::teacher   *TeachF) noexcept;

        layer_descriptor<layer_type>&
         operator= (const layer_descriptor<layer_type>& Ld) noexcept;
      };
    }
  }

  #include "layer_descriptor.cpp"

#endif
