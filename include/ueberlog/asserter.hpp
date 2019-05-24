#ifndef UEBERLOG_ASSERTER_HPP
#define UEBERLOG_ASSERTER_HPP

#include <ueberlog/logger.hpp>

class Asserter {
#if defined NDEBUG
  bool isrelease{true};
#else
  bool isrelease{false};
#endif
  public:
    static Asserter &i() {
      static Asserter inst;
      return inst;
    }

    template<typename ...Args>
    void throw_assert(const bool condition, const char *file, const int line, const char *message, Args ...args) {
      if( !isrelease && !condition ) {
        printf("[ASSERT]: %s in %d line", file, line);
        Logger::i().print(message, args...);
        throw 1;
      }
    }
};

#endif // UEBERLOG_ASSERTER_HPP
