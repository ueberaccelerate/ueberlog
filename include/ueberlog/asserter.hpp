#ifndef UEBERLOG_ASSERTER_HPP
#define UEBERLOG_ASSERTER_HPP

#include <ueberlog/uebercommon.hpp>

namespace ueberlog {
  class Asserter {
  #if defined NDEBUG
    bool isrelease{true};
  #else
    bool isrelease{false};
  #endif
  
    Asserter() = default;
  
    Asserter(const Asserter&) = delete;
    Asserter(Asserter &&) = delete;
    Asserter operator=(const Asserter&) = delete;
    Asserter operator=(Asserter&&) = delete;
    public:
      static Asserter &i() {
        static Asserter inst;
        return inst;
      }
      template<typename ...Args>
      void throw_assert(const bool condition, const char *file, const int line, const char *message, Args&& ...args) const {
        if( !isrelease && !condition ) {
          {
            Color c{Color::red};
            print_log_level(Level::assert, get_timestamp().c_str(), file, line, message, std::forward<Args&&>(args)...);
            print(message, args...);
          }
          assert(condition);
        }
      }
  };
}
#endif // UEBERLOG_ASSERTER_HPP
