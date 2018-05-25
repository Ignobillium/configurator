#ifndef _CONFIGURATOR_
  #define _CONFIGURATOR_

  #ifndef _STD_VECTOR_
    #define _STD_VECTOR_
    #include <vector>
  #endif

  #include "adaptation/__adaptation.hpp"
  #include "layers/__layers.hpp"

  namespace configurator
  {
    class configurator
    {
    private:
      std::vector<configurator::layers::virtual_layer*> OutputLayers;
      std::vector<configurator::layers::virtual_layer*> InputLayers;

      std::vector<configurator::layers::ld_core*> OutputLD;

      netgraph Netgraph;

      std::vector<configurator::adaptation::err_master> ErrMaster;
    public:

      ///
      /// Добавить аналог bad_any_cast для отслеживания ошибок связывания
      /// (вряд ли это кому-то будет нужно, но just4fun и практики можно)
      ///

      // [layer(s) with layer(s)]
        template<typename LType1, typename LType2>
          void bindLayers(layer_descriptor<LType1>& BackLayer,
                          layer_descriptor<LType2>& NextLayer)
                          noexcept;

        template<typename LType1, typename LType2>
          void bindLayers(layer_descriptor<LType1> *BackLayers, size_t LayersCount,
                          layer_descriptor<LType2>& NextLayer)
                          noexcept;

        template<typename LType1, typename LType2>
          void bindLayers(layer_descriptor<LType1>& BackLayer,
                          layer_descriptor<LType2> *NextLayers, size_t LayersCount)
                          noexcept;

        template<typename LType1, typename LType2>
          void bindLayers(layer_descriptor<LType1> *BackLayers, size_t LayersType1Count,
                          layer_descriptor<LType2> *NextLayers, size_t LayersType2Count)
                          noexcept;
      // end [layer(s) with layer(s)]

      // [in/out with layer(s)]
      template<typename LType>
        void bindLayerWithInput(layer_descriptor<LType>& Layer) noexcept;

      template<typename LType>
        void bindLayersWithInput(layer_descriptor<LType> *Layers, size_t LayersCount) noexcept;

      template<typename LType>
        void bindLayerWithOutput(layer_descriptor<LType>& Layer) noexcept;

      template<typename LType>
      void bindLayersWithOutput(layer_descriptor<LType> *Layers, size_t LayersCount) noexcept;
      // end [in/out with layer(s)]

      ///
      /// Запилить ещё bind'ы через итераторы
      ///

      ///
      /// Также в будущем добавить возможность связывать конфигураторы
      ///

      // [assigning (in/out)put layers]
      template<typename LType>
        void regInput(layer_descriptor<LType>& Layer) noexcept;

      template<typename LType>
        void regInput(layer_descriptor<LType> *Layer, size_t LayersCount) noexcept;

      template<typename LType>
        void regOutput(layer_descriptor<LType>& Layer) noexcept;

      template<typename LType>
        void regOutput(layer_descriptor<LType> *Layer, size_t LayersCount) noexcept;
      // end [assigning (in/out)put layers]

      // [core functionality]
        void fillInput(const boost::numeric::ublas::vector<double>* InputData) noexcept;

        void computeIteration() noexcept;
        void teachIteration()   noexcept;

        void teach(bool ExitCondition) noexcept;
        void teach(size_t IterationSount) noexcept;

        void work (size_t IterationSount) noexcept;

        void saveNetgraph(std::ofstream& os) const noexcept;
        void loadLetgraph(std::ofstream& os) noexcept;

        netgraph& compile();
      // end [core functionality]


       configurator() noexcept;
      ~configurator() noexcept;

      configurator(const configurator& Other) noexcept;

      configurator& operator= (const configurator& Other) noexcept;

    private:
      netgraph& fillGenerations() noexcept;
      size_t cnsGenerationsId() noexcept; // cns == Calculate and Set; возвращает число поколений
    };
  }

#endif
