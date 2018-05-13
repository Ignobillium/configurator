ld::layer_descriptor(const ld& Ld)
{
  NeuronsCount = Ld.NeuronsCount;
  InputsCount  = Ld.InputsCount;

  Activator = Ld.Activator;
  Summator = Ld.Summator;
  Teacher = Ld.Teacher;

  Prev = Ld.Prev;

  PrevsCount = Ld.PrevsCount;
  IdQ = Ld.IdQ;
  Visited = Ld.Visited;
}

ld::layer_descriptor(const size_t NC = 1, const size_t IC = 1, const activator ActFunc = _default::Activator, const summator SummFunc = _default::Summator, const teacher TeachFunc = _default::Teacher)
{
  NeuronsCount = NC;
  InputsCount  = IC;

  Activator = ActFunc;
  Summator  = SummFunc;
  Teacher   = TeachFunc;

  PrevsCount = 0;
  IdQ = 0;
  Visited = false;
}

ld::~layer_descriptor()
{
  Prev.clear();
}
