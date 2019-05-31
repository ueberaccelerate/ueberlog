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
      private:
#if defined NDEBUG
      bool isrelease{true};
      Level level{Level::error};
#else
      bool isrelease{false};
      Level level{Level::debug};
#endif
      public:
      template<typename ...Args>
      void debug( const char* function_name, const int line, const char *message, Args&& ...args ) const {
        if( level <= Level::debug ) {
          print_log_level(Level::debug, Color::blue, get_timestamp(), function_name, line, message, std::forward<Args&&>(args)...);
        }
      }
  
      template<typename ...Args>
      void info( const char* function_name, const int line, const char *message, Args&& ...args ) const {
        if( level <= Level::info ) {
          print_log_level(Level::info, Color::cyan, get_timestamp(), function_name, line, message, std::forward<Args&&>(args)...);
        }
      }
      template<typename ...Args>
      void warn( const char* function_name, const int line, const char *message, Args&& ...args ) const {
        if( level <= Level::warn ) {
          print_log_level(Level::warn, Color::yellow, get_timestamp(), function_name, line, message, std::forward<Args&&>(args)...);
        }
      }
      template<typename ...Args>
      void error( const char* function_name, const int line, const char *message, Args&& ...args ) const {
        if( level <= Level::error ) {
          print_log_level(Level::error, Color::red, get_timestamp(), function_name, line, message, std::forward<Args&&>(args)...);
        }
      }
      template<typename ...Args>
      void throw_assert(const bool condition, const char *function_name, const int line, const char *message, Args&& ...args) const {
        if( !isrelease && !condition ) {
          {
            print_log_level(Level::assert, Color::red, get_timestamp().c_str(), function_name, line, message, std::forward<Args&&>(args)...);
          }
          assert(condition);
        }
      }
  };
}
#endif //UEBERLOG_LOGGER_HPP
