std::ostream& operator<<(std::ostream& os, const configurator& Configurator)
{
  os << "\nInputL\n<ld*>: " << Configurator.InputL;
  for(auto p = Configurator.InputL.begin(); p != Configurator.InputL.end(); ++p)
  {

      os << "\n\tNC: " << (*p)->NeuronsCount;
      os << "\n\tIC: " << (*p)->InputsCount;
      os << "\n\tPrevsCount: " << (*p)->PrevsCount;
      os << "\n\tPrev: " << (*p)->Prev;
      os << "\n\tIdQ: " << (*p)->IdQ;
      os << "\n\tVisited: " << (*p)->Visited;

      //os << "\n\tp = " << p;
  }

  os << "\nOutputL\n<ld*>: " << Configurator.OutputL;
  for(auto p = Configurator.OutputL.begin(); p != Configurator.OutputL.end(); ++p)
  {
      //os << "\n\tp = " << p;
      os << "\n\tNC: " << (*p)->NeuronsCount;
      os << "\n\tIC: " << (*p)->InputsCount;
      os << "\n\tPrevsCount: " << (*p)->PrevsCount;
      os << "\n\tPrev: " << (*p)->Prev;
      os << "\n\tIdQ: " << (*p)->IdQ;
      os << "\n\tVisited: " << (*p)->Visited;
  }

  os << "\nBlackBox:\n<ld*>: " << Configurator.BlackBox;
  for(auto p = Configurator.BlackBox.begin(); p != Configurator.BlackBox.end(); ++p)
  {
      //os << "\n\tp = " << p;
      os << "\n\tNC: " << (*p)->NeuronsCount;
      os << "\n\tIC: " << (*p)->InputsCount;
      os << "\n\tPrevsCount: " << (*p)->PrevsCount;
      os << "\n\tPrev: " << (*p)->Prev;
      os << "\n\tIdQ: " << (*p)->IdQ;
      os << "\n\tVisited: " << (*p)->Visited;
  }

  return os;
}
