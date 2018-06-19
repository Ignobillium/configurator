template<typename layer_type>
virtual_layer*
configurator::layers::layer_descriptor<layer_type>::construct() const noexcept
{
  return constructLayer();
}

template<typename layer_type>
layer_type*
configurator::layers::layer_descriptor<layer_type>::constructLayer() const noexcept
{
  return (new layer_type(*this));
}
