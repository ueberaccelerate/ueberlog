#ifndef UEBERLOG_LOGGER_HPP
#define UEBERLOG_LOGGER_HPP

#include <ueberlog/uebercommon.hpp>

namespace ueberlog {
  /* easy logger */
  class Logger {
  
    Logger() = default;
    Logger(const Logger&) = delete;
    Logger(Logger &&) = delete;
    Logger operator=(const Logger&) = delete;
    Logger operator=(Logger&&) = delete;
  
    public:
      static Logger &i() {
        static Logger inst;
        return inst;
      }
      enum class Level {
        debug,
        info,
        warn,
        error
      };
      private:
  #if defined NDEBUG
      Level level{Level::error};
  #else
      Level level{Level::debug};
  #endif
      public:
      template<typename ...Args>
      void debug( const char* file, const int line, const char *message, Args ...args ) {
        if( level <= Level::debug ) {
          std::printf ( "%s [DEBUG]: %s in %d line: ", get_timestamp().c_str(), file, line );
          print  ( message, args...);
        }
      }
  
      template<typename ...Args>
      void info(const char *message, Args ...args ) {
        if( level <= Level::info ) {
          std::printf ( "%s [INFO]: ", get_timestamp().c_str());
          print  ( message, args...);
        }
      }
  
      template<typename ...Args>
      void warn( const char* file, const int line, const char *message, Args ...args ) {
        if( level <= Level::warn ) {
          std::printf ( "%s [WARN]: %s in %d line: ", get_timestamp().c_str(), file, line );
          print  ( message, args...);
        }
      }
  
      template<typename ...Args>
      void error( const char* file, const int line, const char *message, Args ...args ) {
        if( level <= Level::error ) {
          std::printf ( "%s [ERROR]: %s in %d line: ", get_timestamp().c_str(), file, line );
          print  (message, args...);
        }
      }
  
  };
}
#endif //UEBERLOG_LOGGER_HPP
