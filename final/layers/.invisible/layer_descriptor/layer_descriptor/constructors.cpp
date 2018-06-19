template<typename layer_type>
configurator::
layers::
layer_descriptor<layer_type>::layer_descriptor() noexcept
{
  NeuronsCount = 1;
  InputsCount  = 0;

  Activator = DEFAULT_ACTIVATOR;
  Teacher   = DEFAULT_TEACHER;

  GenerationId = 0;
  IsVisited = false;
}

template<typename layer_type>
configurator::
layers::
layer_descriptor<layer_type>::~layer_descriptor() noexcept
{
  // delete Activator;
  // delete Teacher;

  PrevLayers.clear();
}

template<typename layer_type>
configurator::
layers::
layer_descriptor<layer_type>::layer_descriptor(const layer_descriptor<layer_type>& Ld) noexcept
{
  NeuronsCount = Ld.NeuronsCount;
  InputsCount  = Ld.InputsCount;

  Activator = Ld.Activator;
  Teacher   = Ld.Teacher;

  PrevLayers = Ld.PrevLayers;

  GenerationId = Ld.GenerationId;
  IsVisited = Ld.IsVisited;
}

template<typename layer_type>
configurator::
layers::
layer_descriptor<layer_type>::layer_descriptor(const size_t NC,
                const configurator::adaptation::activator *ActF,
                const configurator::adaptation::teacher   *TeachF) noexcept
{
  NeuronsCount = NC;
  InputsCount  = 0;

  Activator = ActF;
  Teacher   = TeachF;

  GenerationId = 0;
  IsVisited = false;
}
