#ifndef UEBERLOG_COMMON_HPP
#define UEBERLOG_COMMON_HPP

#include <array>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <mutex>
#include <utility>

#include <cassert>
#include <cstdio>

#define UEBERLOG_INLINE inline 

namespace ueberlog {
  class Color {
    public:
    enum Type : unsigned {
      red,   // \u001b[31m
      green, // \u001b[32m
      blue,  // \u001b[34m
      cyan,  // \u001b[36m
      yellow,// \u001b[33m
      reset  // \u001b[0m
    };
    Color() = delete;
    Color(const Color &) = delete;
    Color(Color &&) = delete;
    Color operator=(const Color&) = delete;
    Color operator=(Color&&) = delete;


    explicit Color (const Type color) {
      set_color(color);
    }
    ~Color() {
      set_color(reset);
    }
    void set_color ( Type color ) const {
      const std::array<const char*, 6> colors_ {"\u001b[31m", "\u001b[32m", "\u001b[34m", "\u001b[36m", "\u001b[33m", "\u001b[0m"};
      printf("%s", colors_[color] );
    }
  };
  enum class Level {
    debug,
    info,
    warn,
    error,
    assert
  };
  class ULogger {
    ULogger() = default;
    ULogger(const ULogger &) = delete;
    ULogger(ULogger &&) = delete;
    ULogger operator=(const ULogger&) = delete;
    ULogger operator=(ULogger&&) = delete;
#ifdef THREAD_SAFE
    std::mutex &logger_mutex = []() -> std::mutex& {static std::mutex inst; return inst; }();
#endif
    public:
    static ULogger &i() {
      static ULogger inst;
      return inst;
    }
    UEBERLOG_INLINE std::string level_to_string(const Level level) {
      switch(level) {
        case Level::debug:  return "DEBUG";
        case Level::info:   return "INFO";
        case Level::warn:   return "WARN";
        case Level::error:  return "ERROR";
        case Level::assert: return "ASSERT";
        default: return "";
      }
    }
    UEBERLOG_INLINE std::string get_timestamp() {
      auto now = std::chrono::system_clock::now();
      std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
      std::stringstream ss;
      ss << std::put_time(std::localtime(&now_c), "%F %T");
      return ss.str();
    }
    template <typename ...Args>
    UEBERLOG_INLINE void print( const char * const message, Args&& ...args) {
      char *point = const_cast<char *>(message);
      int argscount{0};
      while(*point != '\0') {
        if( *point == '%' ) argscount++;
        point++;
      }
      if( argscount == sizeof...(args) ) {
        std::printf (message, std::forward<Args&&>(args)...);
      }
    }
    template<>
    UEBERLOG_INLINE void print( const char *message) {
      std::printf ("%s", message);
    }

    template<typename ...Args>
    UEBERLOG_INLINE void print_log_level(const Level level, const Color::Type &color,
                          const char* function_name, const int line, const char *message, Args&& ...args) {
#ifdef THREAD_SAFE
      [[maybe_unused]] std::lock_guard<std::mutex> lk(logger_mutex);
#endif
      Color c{color};
      std::printf( "%s [%s %s:%d]:", get_timestamp().c_str(), level_to_string(level).c_str(), function_name, line );
      print( message, std::forward<Args&&>(args)... );
    }
  };
}
#endif // UEBERLOG_COMMON_HPP
