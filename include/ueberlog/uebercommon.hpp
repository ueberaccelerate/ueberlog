#ifndef UEBERLOG_COMMON_HPP
#define UEBERLOG_COMMON_HPP

#include <array>
#include <chrono>
#include <iomanip>
#include <sstream>

#include <cstdio>

namespace ueberlog {
  class Color {
    public:
    enum Type : unsigned {
      red,   // \u001b[31m
      green, // \u001b[32m
      blue,  // \u001b[34m
      cyan,  // \u001b[36m
      yellow,
      reset
    };
    void set_color ( Type color ) const {
      const std::array<const char*, 6> colors_ {"\u001b[31m", "\u001b[32m", "\u001b[34m", "\u001b[36m", "\u001b[33m", "\u001b[0m"};
      printf("%s", colors_[color] );
    }
    Color (const Type color) {
      set_color(color);
    }
    ~Color() {
      set_color(reset);
    }
  };
  enum class Level {
    debug,
    info,
    warn,
    error,
    assert
  };
  std::string level_to_string(const Level level) {
    switch(level) {
      case Level::debug:  return "DEBUG";
      case Level::info:   return "INFO";
      case Level::warn:   return "WARN";
      case Level::error:  return "ERROR";
      case Level::assert: return "ASSERT";
      default: return "";
    }
  }
  std::string get_timestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%F %T");
    return ss.str();
  }
  template <typename ...Args>
  void print( const char *message, Args ...args) {
    char *point = const_cast<char *>(message);
    int argscount{0};
    while(*point != '\0') {
      if( *point == '%' ) argscount++;
      point++;
    }
    if( argscount == sizeof...(args) ) {
      std::printf (message, args...);
    }
  }
  template<>
  void print( const char *message) {
    std::printf ("%s", message);
  }

  template<typename ...Args>
  void print_log_level(const Level level, const std::string& timestamp, const char* file, const int line, const char *message, Args ...args) {
    std::printf( "%s [%s]: %s in %d line: ", timestamp.c_str(), level_to_string(level).c_str(), file, line );
    print( message, args... );
  }
}
#endif // UEBERLOG_COMMON_HPP
