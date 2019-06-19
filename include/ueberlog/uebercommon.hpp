#ifndef UEBERLOG_COMMON_HPP
#define UEBERLOG_COMMON_HPP

#include <array>
#include <chrono>
#include <iomanip>
#include <mutex>
#include <sstream>
#include <utility>

#include <cassert>
#include <cstdio>

#define UEBERLOG_INLINE inline

namespace ueberlog {
class nocopimovable {
 public:
  nocopimovable() = default;
  nocopimovable(const nocopimovable &) = delete;
  nocopimovable(nocopimovable &&) = delete;
  nocopimovable operator=(const nocopimovable &) = delete;
  nocopimovable operator=(nocopimovable &&) = delete;
};
class Color : public nocopimovable {
 public:
  enum class Type : unsigned char {
    red = 0,  // \u001b[31m
    green,    // \u001b[32m
    blue,     // \u001b[34m
    cyan,     // \u001b[36m
    yellow,   // \u001b[33m
    reset     // \u001b[0m
  };

  inline static constexpr Type red = Type::red;        // \u001b[31m
  inline static constexpr Type green = Type::green;    // \u001b[32m
  inline static constexpr Type blue = Type::blue;      // \u001b[34m
  inline static constexpr Type cyan = Type::cyan;      // \u001b[36m
  inline static constexpr Type yellow = Type::yellow;  // \u001b[33m
  inline static constexpr Type reset = Type::reset;    // \u001b[0m

  Color() = delete;

  explicit Color(const Type color) { set_color(color); }
  ~Color() { set_color(reset); }
  void set_color(const Type color) const noexcept {
    constexpr std::array<const char *, 6> colors_{"\u001b[31m", "\u001b[32m",
                                                  "\u001b[34m", "\u001b[36m",
                                                  "\u001b[33m", "\u001b[0m"};
    printf("%s", colors_[static_cast<std::size_t>(color)]);
  }
};
enum class Level { debug, info, warn, error, assert };
struct LogInfo {
  Level level;
  Color color;
  std::string function_name;
  std::size_t line;
};
class ULogger : public nocopimovable {
  ULogger() = default;
#ifdef THREAD_SAFE
  std::mutex &logger_mutex = []() -> std::mutex & {
    static std::mutex inst;
    return inst;
  }();
#endif
 public:
  static ULogger &i() {
    static ULogger inst;
    return inst;
  }
  UEBERLOG_INLINE std::string level_to_string(const Level level) const noexcept{
    switch (level) {
      case Level::debug:
        return "DEBUG";
      case Level::info:
        return "INFO";
      case Level::warn:
        return "WARN";
      case Level::error:
        return "ERROR";
      case Level::assert:
        return "ASSERT";
      default:
        return "";
    }
  }
  UEBERLOG_INLINE std::string get_timestamp() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_c =
        std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_c), "%F %T");
    return ss.str();
  }
  template <typename... Args>
  UEBERLOG_INLINE void print(const LogInfo &loginfo, const char *const message,
                             Args &&... args) {
    char *point = const_cast<char *>(message);
    int argscount{0};
    while (*point != '\0') {
      if (*point == '%') argscount++;
      point++;
    }
    if (argscount == sizeof...(args)) {
      char buffer[256];
      std::sprintf(buffer, "%s [%s %s:%lu]:", get_timestamp().c_str(),
                   level_to_string(loginfo.level).c_str(),
                   loginfo.function_name.c_str(), loginfo.line);
      std::printf("%s", buffer);
      std::printf(message, std::forward<Args &&>(args)...);
    }
  }

  template <typename... Args>
  UEBERLOG_INLINE void print_log_level(const Level level,
                                       const Color::Type &color,
                                       const char *function_name,
                                       const std::size_t line,
                                       const char *message, Args &&... args) {
#ifdef THREAD_SAFE
    [[maybe_unused]] std::lock_guard<std::mutex> lk(logger_mutex);
#endif
    print(LogInfo{level, Color{color}, function_name, line}, message,
          std::forward<Args &&>(args)...);
  }
};
}  // namespace ueberlog
#endif  // UEBERLOG_COMMON_HPP
