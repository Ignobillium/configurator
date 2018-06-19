# configurator
*** Configurator v2.0.1 betha ***
* Proof of Concept, минимальный необходимый функционал *


Что нужно знать:
  1) Включаемый файл - network.hpp (но если очень хочется, можно включить network.cpp); его более чем достаточно; Дефолтом содержит в себе <iostream>, <fstream>, <algorithm>, <utility>, <vector> и <time.h>

  2) В __infrastructure и configurator можно не лазить, если нет желания провести ПОЛНУЮ ручную настройку сети (тем более сейчас она может не сработать вследствие некоторой костыльности в функции corrWeights).
    Ради интереса можно глянуть __t-defs и __default_solutions

  3) Конструирование сети производится довольно просто:
    - в теле основной программы создаёте объекты layer_descriptor в необходимом количестве; обязательно необходимо создать объект под входной и выходной слои. Объект можно создать двумя способами:
      а) "ленивый метод": при инициации объекта указывается число нейронов:

          layer_descriptor Layer(10); // создаёт layer_descriptor с десятью нейронами

      б) "ленивый с извращённым входом": при инициации объекта после числа нейронов указывается число входных каналов; не стоит заморачиваться при подсчёте числа входов для каждого скрытого слоя и слоя выхода, за вас это сделает программа; этот метод эффективен исключительно для создания входных слоёв. Зачем? Во-первых, just for fun, а во-вторых: мало ли что в жизни пригодится? Но хватит слов

          layer_descriptor i1(1, 2); // создаёт входной слой из одного нейрона (да, так тоже можно), имеющего два входа; т.е. по факту на вход сети подаётся два значения

      в) "с заданием активационной функции": да, всё правильно. Тут можно задать каждому слою свою активационную функцию. На данный момент в качестве активационной функции используется сигмоида f = 1 / ( 1 + exp(-x)). Чтобы задать активационную функцию используется тип activator (суть указатель на double функцию, принимающую один параметр double). Код:

          <...>
          double X2(double x) { return sqr(x); }
          <...>
          activator Activator = &X2;
          layer_descriptor Ld(10, 1, Activator);
          // будет создан слой с 10 нейронами и активационной функцией sqr(x)

    - как только будут созданы все необходимые объекты layer_descriptor, их необходимо зарегистрировать объектом configurator; тут тоже довольно простая схема: создаём объект и используем функции regInput для регистрации входных слоёв, regOutput для регистрации выходных слоёв, regBlackBox для ркгистрации скрытых, указывая параметром функции указатель на объект layer_descriptor

        configurator Configurator; // создание объекта Configurator
        Configurator.regInput(&i1);
        Configurator.regOutput(&Ld);
        Configurator.regBlackBox(&Layer);

    - после регистрации всех слоёв необходимо их связать согласно конфигурации (топологии), которая вам необходима. Для этого используется функция BindLayers в нескольких вариациях:

        void BindLayers(std::vector<ld> *Current, std::vector<ld> *Next);

          void BindLayers(ld *Current, ld *Next);
          void BindLayers(ld *Current, std::vector<ld> *Next);
          void BindLayers(std::vector<ld> *Current, ld *Next);

            inline void BindIwL(std::vector<ld> *Current);
              void BindIwL(ld* Current);

            inline void BindOwL(std::vector<ld> *Current);
              void BindOwL(ld* Current);

       если нет необходимости регистрировать слои в промышленных масштабах, используйте функции

          void BindLayers(ld *Current, ld *Next) чтобы связать два слоя (непринципиально, каких)

          void BindIwL(ld* Current) чтобы связать слой Current со ВСЕМИ входными слоями

          void BindOwL(ld* Current) чтобы связать слой Current со ВСЕМИ выходными слоями

    - как только всё будет связано, скомпилируйте сеть

        network Net = network(Configurator.compile());

  4) готово, теперь сеть можно использовать
      методы
          inline void teach(bool exitCondition, std::istream& DataStream, std::istream& ExpStream, std::ostream& Output)

          inline void teach(bool exitCondition, std::ifstream& DataStream, std::ifstream& ExpStream, std::ofstream& Output)

          inline void teach(size_t iterationsCount, std::istream& DataStream, std::istream& ExpStream, std::ostream& Output)

          inline void teach(size_t iterationsCount, std::ifstream& DataStream, std::ifstream& ExpStream, std::ofstream& Output)
       обучают сеть,
       здесь
          bool exitCondition - условие завершения обучения;
          size_t iterationsCount - число итераций обучения;
          DataStream -- поток входных данных
          ExpStream -- поток ожиданий
          Output -- поток для сохранения сети (пока недопилена загрузка сети из сохранений)

      методы
          void work(bool exitCondition, std::istream& DataStream, std::ostream& Output)

          void work(bool exitCondition, std::ifstream& DataStream, std::ofstream& Output)

          void work(size_t iterationsCount, std::istream& DataStream, std::ostream& Output)

          void work(size_t iterationsCount, std::ifstream& DataStream, std::ofstream& Output)

      прогоняют данные из DataStream через сеть и сохраняют результат в Output



*******************************************
      Примечания
*******************************************

0) компилировать с ключом совместимости с++14
Для g++ это будет

  $ g++ -o fname --std=c++14 file.cpp

1) Функции обучения можно пилить вручную, если не устраивает градиентный спуск, но тут уже ответсвенность не на мне;
  Механика:

  функция обучения возвращает double значение поправки к весу исходя из параметров
      double Input - вход текущей связи
      double TotalOutput - выходное значение нейрона (после активации)
      double Error - ошибка нейрона
      activator ActFunc - активационная функция нейрона (та же, что для слоя)

    собственно вот её определение:

    using teacher = double(*)(double Input, double TotalOutput, double Error, activator ActFunc);

*******************************************
      Перспективы
*******************************************

0) constexpr explicit noexcept конструкторы для ускорения работы программы
1) constexpr функции для компиляции сети во время компиляции программы

2) консольный интерфейс для конструирования сети без написания кода
2.5) добавление поддержки сохранений и загрузок
2.75) улучшение методов ввода-вывода
2.8) механика dropout
2.9) вычисление времени работы сети

3) символьные вычисления для повышения точности
3.5) constexpr символьные вычисления

4) распараллеливание алгоритма с использованием omp/mpi/cuda/openCL/corba/комбинации этих технологий
5) флаги препроцессора для оптимизации алгоритмов по скорости/памяти

6) добавление библиотеки стандартных решений для быстрой настройки под известные конфигурации

7) переход от static-конфигурации к динамической самоорганизации

*******************************************
      Внесённые исправления
*******************************************

0) добавлены смещения
1) теперь каждому слою можно задать собственную активационную функцию
