#ifndef UEBERLOG_COMMON_HPP
#define UEBERLOG_COMMON_HPP

#include <chrono>
#include <iomanip>
#include <sstream>

#include <cstdio>

namespace ueberlog {
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
}
#endif // UEBERLOG_COMMON_HPP
