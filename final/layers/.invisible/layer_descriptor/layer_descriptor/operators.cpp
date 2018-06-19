template<typename layer_type>
layer_descriptor<layer_type>&
configurator::layers::layer_descriptor<layer_type>::
 operator= (const layer_descriptor<layer_type>& Ld) noexcept
{
  if (this != &Ld)
  {
    NeuronsCount = Ld.NeuronsCount;
    InputsCount  = Ld.InputsCount;

    Activator = Ld.Activator;
    Teacher = Ld.Teacher;

    PrevLayers.clear();
    PrevLayers = Ld.PrevLayers;

    GenerationId = Ld.GenerationId;
    IsVisited = Ld.IsVisited;
  }

  return *this;
}
