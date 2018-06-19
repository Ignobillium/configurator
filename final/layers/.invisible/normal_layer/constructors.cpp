configurator::layers::normal_layer() noexcept
{

}
configurator::layers::~normal_layer() noexcept
{
  delete[] Weights;
  // delete Activator;
  // delete Teacher;

  // + очистка векторов, если она не производится автоматически
}

configurator::layers::normal_layer(const normal_layer& Other) noexcept
{
  Weights = Other.Weights;

  Bias = Other.Bias;
  Error = Other.Error;

  Output = Other.Output;
  ActivateOutput = Other.ActivateOutput;

  Activator = Other.Activator;
  Teacher = Other.Teacher;

  PrevLayersCount = Other.PrevLayersCount;

  if(PrevLayers)
    delete[] PrevLayers;
  PrevLayers = new virtual_layer*[PrevLayersCount];
  for(size_t i = 0; i < PrevLayersCount; ++i)
    PrevLayers[i] = Other.PrevLayers[i];
}

configurator::layers::normal_layer(const layer_descriptor<normal_layer>& Ld) noexcept
{

}
