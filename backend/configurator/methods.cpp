void configurator::regInput(std::vector<ld> iL)
{
  for(size_t i = 0; i < iL.size(); ++i)
  {
    InputL.push_back( &( iL[i] ) );
    iL[i].PrevsCount = 1;
    iL[i].Prev.clear();
  }
  std::cout << "\n current inputL: " << InputL;
}

void configurator::regInput(ld *iL)
{
  InputL.push_back( iL );
  iL->PrevsCount = 1;
  iL->Prev.clear();
  std::cout << "\n current inputL: " << InputL;
}

void configurator::regOutput(std::vector<ld> oL)
{
  for(size_t i = 0; i < oL.size(); ++i)
  {
    OutputL.push_back( &( oL[i] ) );

    oL[i].InputsCount = 0;
    oL[i].PrevsCount = 0;
    oL[i].Prev.clear();
  }
  std::cout << "\n current outputL: " << OutputL;
}

void configurator::regOutput(ld *oL)
{
  OutputL.push_back( oL );

  oL->InputsCount = 0;
  oL->PrevsCount = 0;
  oL->Prev.clear();
  std::cout << "\n current outputL: " << OutputL;
}

void configurator::regBlackBox(std::vector<ld> bB)
{
  for(size_t i = 0; i < bB.size(); ++i)
  {
    BlackBox.push_back( &( bB[i] ) );

    bB[i].InputsCount = 0;
    bB[i].PrevsCount = 0;
    bB[i].Prev.clear();
  }
  std::cout << "\n current blackB: " << BlackBox;
}

void configurator::regBlackBox(ld *bB)
{
  BlackBox.push_back( bB );

  bB->InputsCount = 0;
  bB->PrevsCount = 0;
  bB->Prev.clear();
  std::cout << "\n current blackB: " << BlackBox;
}


void configurator::BindLayers(std::vector<ld> *Current, std::vector<ld> *Next)
{
  for(auto p = Next->begin(); p != Next->end(); ++p)
  {
    size_t curId = 0;
    for(auto j = Current->begin(); j != Current->end(); ++j, ++curId)
    {
      p->Prev.push_back( &( (*Current)[curId] ) );
      p->InputsCount += 1;
    }
  }
  std::cout << "\n current blackB: " << BlackBox;
}

void configurator::BindLayers(ld *Current, ld *Next)
{
  Next->Prev.push_back( Current );
  Next->InputsCount += 1;
  std::cout << "\n current blackB: " << BlackBox;
}

void configurator::BindLayers(ld *Current, std::vector<ld> *Next)
{
  for(auto p = Next->begin(); p != Next->end(); ++p)
  {
    p->Prev.push_back( Current );
    p->InputsCount += 1;
  }
  std::cout << "\n current blackB: " << BlackBox;
}

void configurator::BindLayers(std::vector<ld> *Current, ld *Next)
{
  for(size_t j = 0; j < Current->size(); ++j)
  {
    Next->Prev.push_back( &(*Current)[j] );
    ++Next->InputsCount;
  }
  std::cout << "\n current blackB: " << BlackBox;
}

inline void configurator::BindIwL(std::vector<ld> *Current)
{
  for(auto p = Current->begin(); p != Current->end(); ++p)
    for(size_t j = 0; j < InputL.size(); ++j)
    {
      p->Prev.push_back( InputL[j] );
      p->InputsCount += 1;
    }
    std::cout << "\n current blackB: " << BlackBox;
    std::cout << "\n current inputL: " << InputL;
}

void configurator::BindIwL(ld* Current)
{
  for(size_t j = 0; j < InputL.size(); ++j)
  {
    Current->Prev.push_back( InputL[j] );
    Current->InputsCount += 1;
  }
  std::cout << "\n current blackB: " << BlackBox;
  std::cout << "\n current inputL: " << InputL;
}

inline void configurator::BindOwL(std::vector<ld> *Current)
{
  for(size_t i = 0; i < OutputL.size(); ++i)
    for(size_t j = 0; j < Current->size(); ++j)
    {
      OutputL[i]->Prev.push_back( &(*Current)[j] );
      ++OutputL[i]->InputsCount;
    }
    std::cout << "\n current blackB: " << BlackBox;
    std::cout << "\n current outputL: " << OutputL;
}

void configurator::BindOwL(ld* Current)
{
  for(size_t i = 0; i < OutputL.size(); ++i)
  {
    OutputL[i]->Prev.push_back( Current );
    OutputL[i]->InputsCount += 1;
  }
  std::cout << "\n current blackB: " << BlackBox;
  std::cout << "\n current outputL: " << OutputL;
}

#include "compile.cpp"
