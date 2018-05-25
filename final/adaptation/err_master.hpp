#ifndef _ERR_MASTER_
#define _ERR_MASTER_

  namespace configurator
  {
    namespace adaptation
    {
      class err_master
      {
      public:
        virtual void calculateError(virtual_layer& Vl) noexcept = 0;
        virtual void propogateError(virtual_layer& Vl) noexcept = 0;

                 err_master() noexcept {}
        virtual ~err_master() noexcept {}
      };
    }
  }

#endif
