#ifndef _ACTIVATOR_
  #define _ACTIVATOR_

  namespace configurator
  {
    namespace adaptation
    {
      class activator
      {
      public:
        virtual boost::numeric::ublas::vector<double>&
         activate(const boost::numeric::ublas::vector<double>& Data) noexcept = 0;

                 activator() noexcept {}
        virtual ~activator() noexcept {}
      };
    }
  }

#endif
