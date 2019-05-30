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
#ifdef THREAD_SAFE
      std::mutex &logger_mutex = [] () -> std::mutex& {static std::mutex m; return m;}();
#endif
      public:
      template<typename ...Args>
      void debug( const char* function_name, const int line, const char *message, Args&& ...args ) const {
#ifdef THREAD_SAFE
        [[maybe_unused]] std::lock_guard<std::mutex> lk(logger_mutex);
#endif
        if( level <= Level::debug ) {
          Color c{Color::blue};
          print_log_level(Level::debug, get_timestamp(), function_name, line, message, std::forward<Args&&>(args)...);
        }
      }
  
      template<typename ...Args>
      void info( const char* function_name, const int line, const char *message, Args&& ...args ) const {
#ifdef THREAD_SAFE
        [[maybe_unused]] std::lock_guard<std::mutex> lk(logger_mutex);
#endif
        if( level <= Level::info ) {
          Color c{Color::cyan};
          print_log_level(Level::info, get_timestamp(), function_name, line, message, std::forward<Args&&>(args)...);
        }
      }
  
      template<typename ...Args>
      void warn( const char* function_name, const int line, const char *message, Args&& ...args ) const {
#ifdef THREAD_SAFE
        [[maybe_unused]] std::lock_guard<std::mutex> lk(logger_mutex);
#endif
        if( level <= Level::warn ) {
          Color c{Color::yellow};
          print_log_level(Level::warn, get_timestamp(), function_name, line, message, std::forward<Args&&>(args)...);
        }
      }
  
      template<typename ...Args>
      void error( const char* function_name, const int line, const char *message, Args&& ...args ) const {
#ifdef THREAD_SAFE
        [[maybe_unused]] std::lock_guard<std::mutex> lk(logger_mutex);
#endif
        if( level <= Level::error ) {
          Color c{Color::red};
          print_log_level(Level::error, get_timestamp(), function_name, line, message, std::forward<Args&&>(args)...);
        }
      }
      template<typename ...Args>
      void throw_assert(const bool condition, const char *function_name, const int line, const char *message, Args&& ...args) const {
#ifdef THREAD_SAFE
        [[maybe_unused]] std::lock_guard<std::mutex> lk(logger_mutex);
#endif
        if( !isrelease && !condition ) {
          {
            Color c{Color::red};
            print_log_level(Level::assert, get_timestamp().c_str(), function_name, line, message, std::forward<Args&&>(args)...);
            print(message, args...);
          }
          assert(condition);
        }
      }
  };
}
#endif //UEBERLOG_LOGGER_HPP
