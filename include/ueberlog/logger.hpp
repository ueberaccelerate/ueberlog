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
      std::string level_to_string(const Level level) const {
        switch(level) {
          case Level::debug: return "DEBUG";
          case Level::info:  return "INFO";
          case Level::warn:  return "WARN";
          case Level::error: return "ERROR";
          default: return "";
        }
      }
      template<typename ...Args>
      void print_log_level(const Level level, const std::string& timestamp, const char* file, const int line, const char *message, Args ...args) const {
        std::printf( "%s [%s]: %s in %d line: ", timestamp.c_str(), level_to_string(level).c_str(), file, line );
        print( message, args... );
      }
      public:

      template<typename ...Args>
      void debug( const char* file, const int line, const char *message, Args ...args ) const {
        if( level <= Level::debug ) {
          Color c{Color::blue};
          print_log_level(Level::debug, get_timestamp(), file, line, message, args...);
        }
      }
  
      template<typename ...Args>
      void info( const char* file, const int line, const char *message, Args ...args ) const {
        if( level <= Level::info ) {
          Color c{Color::cyan};
          print_log_level(Level::info, get_timestamp(), file, line, message, args...);
        }
      }
  
      template<typename ...Args>
      void warn( const char* file, const int line, const char *message, Args ...args ) const {
        if( level <= Level::warn ) {
          Color c{Color::yellow};
          print_log_level(Level::warn, get_timestamp(), file, line, message, args...);
        }
      }
  
      template<typename ...Args>
      void error( const char* file, const int line, const char *message, Args ...args ) const {
        if( level <= Level::error ) {
          Color c{Color::red};
          print_log_level(Level::error, get_timestamp(), file, line, message, args...);
        }
      }
  };
}
#endif //UEBERLOG_LOGGER_HPP
