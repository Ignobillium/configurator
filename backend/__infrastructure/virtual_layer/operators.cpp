vl& vl::operator=(const vl& Vl)
{
  Weights = Vl.Weights;
  Bias    = Vl.Bias;
  Error   = Vl.Error;

  ConfRule = Vl.ConfRule;

  Activator = Vl.Activator;
  Summator = Vl.Summator;
  Teacher = Vl.Teacher;
}

std::ostream& operator<<(std::ostream& os, const vl& Vl)
{
    os << '\n' << "Weights:";
    size_t channel = 0;
    for(auto p = Vl.Weights.begin(); p != Vl.Weights.end(); ++p, ++channel)
    {
      os << "\nchannel[" << channel << "]:";
      size_t neuron = 0;
      for( auto j = p->begin(); j != p->end(); ++j, ++neuron)
      {
        os << "\n\tneuron[" << neuron << "]: ";
        for(auto k = j->begin(); k != j->end(); ++k)
          os << *k <<  ' ';
      }
    }
    os << '\n' << "Bias: " << Vl.Bias;
    os << '\n' << "Error: " << Vl.Error;
    os << '\n' << "ConfRule:\n" << Vl.ConfRule;

    os << "\nSizes:";
    os << "\n\tChannelsCount: " << Vl.Weights.size() << "\n\tNeuronsCount:" << Vl.Error.size() << '\n';

    return os;
}
