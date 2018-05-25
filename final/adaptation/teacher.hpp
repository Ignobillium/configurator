#ifndef _TEACHER_
  #define _TEACHER_

  namespace configurator
  {
    namespace adaptation
    {
      class teacher
      {
      public:
        virtual void teach(virtual_layer& Vl) noexcept = 0;

                 teacher() noexcept {}
        virtual ~teacher() noexcept {}
      };
    }
  }

#endif
