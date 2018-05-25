#ifndef _LAYERS_
  #define _LAYERS_

    #ifndef _STD_VECTOR_
      #define _STD_VECTOR_
      #include <vector>
    #endif

  class configurator::layers::virtual_layer;
  class configurator::layers::layer_descriptor;

  class configurator::adaptation::activator;
  class configurator::adaptation::teacher;

  #include "layer_descriptor.hpp"
  #include "virtual_layer.hpp"
  #include "normal_layer.hpp"
  #include "recurrent_layer.hpp"

#endif
