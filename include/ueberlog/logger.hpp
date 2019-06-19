#ifndef UEBERLOG_LOGGER_HPP
#define UEBERLOG_LOGGER_HPP

#include <ueberlog/uebercommon.hpp>

namespace ueberlog {
/* easy logger */
class Logger : public nocopimovable {
  Logger() = default;

 public:
  static Logger& i() {
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
  template <typename... Args>
  void debug(const char* function_name, const int line, const char* message,
             Args&&... args) const {
    if (level <= Level::debug) {
      ULogger::i().print_log_level(Level::debug, Color::blue, function_name,
                                   line, message,
                                   std::forward<Args&&>(args)...);
    }
  }

  template <typename... Args>
  void info(const char* function_name, const int line, const char* message,
            Args&&... args) const {
    if (level <= Level::info) {
      ULogger::i().print_log_level(Level::info, Color::cyan, function_name,
                                   line, message,
                                   std::forward<Args&&>(args)...);
    }
  }
  template <typename... Args>
  void warn(const char* function_name, const int line, const char* message,
            Args&&... args) const {
    if (level <= Level::warn) {
      ULogger::i().print_log_level(Level::warn, Color::yellow, function_name,
                                   line, message,
                                   std::forward<Args&&>(args)...);
    }
  }
  template <typename... Args>
  void error(const char* function_name, const int line, const char* message,
             Args&&... args) const {
    if (level <= Level::error) {
      ULogger::i().print_log_level(Level::error, Color::red, function_name,
                                   line, message,
                                   std::forward<Args&&>(args)...);
    }
  }
  template <typename... Args>
  void throw_assert(const bool condition, const char* function_name,
                    const int line, const char* message, Args&&... args) const {
    if (!isrelease && !condition) {
      {
        ULogger::i().print_log_level(Level::assert, Color::red, function_name,
                                     line, message,
                                     std::forward<Args&&>(args)...);
      }
      assert(condition);
    }
  }
};
}  // namespace ueberlog
#endif  // UEBERLOG_LOGGER_HPP
