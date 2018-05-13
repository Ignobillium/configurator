#ifndef _ALGORITHM_
  #include <algorithm>
  #define _ALGORITHM_
#endif

void calculatePrevs(size_t *Next, ld* Ld)
{
  if( !(Ld->Visited) )
  {
    if( !( Ld->Prev.empty() ) )
    {
      for(size_t i = 0; i < Ld->Prev.size(); ++i)
        calculatePrevs( &(Ld->PrevsCount), Ld->Prev[i]);
      Ld->Visited = true;
    }
  }
  *Next += Ld->PrevsCount;
}

std::vector<q_generation> configurator::compile()
{
  std::vector<q_generation> Res;

  // 1 - организовать в правильном порядке слои
  for(size_t i = 0; i < OutputL.size(); ++i)
    calculatePrevs( &(OutputL[i]->PrevsCount), OutputL[i] );

  sort(BlackBox.begin(), BlackBox.end(), [](const ld* First, const ld* Second){ return First->PrevsCount < Second->PrevsCount;});

  // 2 - подготавливаем данные для создания очереди
  q_generation  qgTemp;

      // закидываем в начало очереди InputL
        for(size_t i = 0; i < InputL.size(); ++i)
        {
          InputL[i]->PrevsCount = 0;
          InputL[i]->IdQ        = i;

          qgTemp.Layers.push_back( virtual_layer ( *(InputL[i]) ) );
          qgTemp.Output.push_back( std::vector<double>(InputL[i]->NeuronsCount) );
          qgTemp.Data.push_back( std::vector<double>(InputL[i]->NeuronsCount) );
        }
        // ------------------------
          Res.push_back(qgTemp);
            qgTemp.Layers.clear();
            qgTemp.Output.clear();
            qgTemp.Data.clear();
        //     подчистили хвосты

      // теперь закидываем BlackBox
        size_t CurrentGeneration = BlackBox[0]->PrevsCount;
        size_t VirtualGeneration = 1;
        size_t CurrentIdQ = 0;

        for(size_t i = 0; i < BlackBox.size(); ++i)
        {
          // оптимизировать !
          if( BlackBox[i]->PrevsCount == CurrentGeneration )
          {
            BlackBox[i]->PrevsCount = VirtualGeneration;
            BlackBox[i]->IdQ        = CurrentIdQ;
            ++CurrentIdQ;

            qgTemp.Layers.push_back( virtual_layer( *(BlackBox[i])) );
            qgTemp.Output.push_back( std::vector<double>(BlackBox[i]->NeuronsCount) );
            qgTemp.Data.push_back( std::vector<double>(BlackBox[i]->NeuronsCount) );
          }
          else
          {
            Res.push_back(qgTemp);

            // чистим хвосты
            qgTemp.Layers.clear();
            qgTemp.Output.clear();
            qgTemp.Data.clear();

            VirtualGeneration++;
            CurrentGeneration = BlackBox[i]->PrevsCount;

            CurrentIdQ = 0;



            BlackBox[i]->PrevsCount = VirtualGeneration;
            BlackBox[i]->IdQ        = CurrentIdQ;
            ++CurrentIdQ;

            qgTemp.Layers.push_back( virtual_layer( *(BlackBox[i])) );
            qgTemp.Output.push_back( std::vector<double>(BlackBox[i]->NeuronsCount) );
            qgTemp.Data.push_back( std::vector<double>(BlackBox[i]->NeuronsCount) );
          }
        }
      // ------------------------
        Res.push_back(qgTemp);
          qgTemp.Layers.clear();
          qgTemp.Output.clear();
          qgTemp.Data.clear();
      //      подчистили хвосты

      // закинули BlackBox

      // дело за малым -- закинуть OutputL
        for(size_t i = 0; i < OutputL.size(); ++i)
        {
          qgTemp.Layers.push_back( virtual_layer ( *(OutputL[i]) ) );
          qgTemp.Output.push_back( std::vector<double>(OutputL[i]->NeuronsCount) );
          qgTemp.Data.push_back( std::vector<double>(OutputL[i]->NeuronsCount) );
        }
        // -------------------
          Res.push_back(qgTemp);
            qgTemp.Layers.clear();
            qgTemp.Output.clear();
            qgTemp.Data.clear();
        //    подчистили хвосты
      // done
  return Res;
}
