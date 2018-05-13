configurator::configurator()
{

}

configurator::configurator(const configurator& Configurator)
{
  InputL   = Configurator.InputL;
  OutputL  = Configurator.OutputL;
  BlackBox = Configurator.BlackBox;
}

configurator::~configurator()
{
  InputL.clear();
  OutputL.clear();
  BlackBox.clear();
}
