#ifndef _NETGRAPH_
  #define _NETGRAPH_

  namespace configurator
  {
    class netgraph
    {
    protected:
      configurator::layers::virtual_layer** NetgraphGenerationQuant;

      size_t  GenerationsCount;
      size_t *GenerationQuantsCount;
    public:
      void fillGeneration(const size_t GenerationIndex,
                          const configurator::layers::virtual_layer* Layers);
      /// TODO:
      /// Добавить аналог bad_any_cast для отслеживания ошибок заполнения
      ///

       netgraph() noexcept;
      ~netgraph() noexcept;

      netgraph(const size_t  generationsCount)      noexcept;
      netgraph(const size_t  generationsCount,
               const size_t *generationQuantsCount) noexcept;


      netgraph(const netgraph& Other) noexcept;

      netgraph& operator= (const netgraph& NG) noexcept;
    };
  }

#endif
