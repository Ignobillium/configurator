ld& ld::operator=(const ld& Ld)
{
  NeuronsCount = Ld.NeuronsCount;
  InputsCount  = Ld.InputsCount;

  Activator = Ld.Activator;
  Summator = Ld.Summator;
  Teacher = Ld.Teacher;

  Prev = Ld.Prev;

  PrevsCount = Ld.PrevsCount;
  IdQ = Ld.PrevsCount;
  Visited = Ld.Visited;
}

std::ostream& operator<<(std::ostream& os, const ld& Ld)
{
  os << '\n' << Ld.NeuronsCount;
  os << '\n' << Ld.InputsCount;
  os << '\n' << Ld.PrevsCount;
  os << '\n' << Ld.IdQ;
  os << '\n' << Ld.Prev;
  os << '\n' << Ld.Visited;

  return os;
}
