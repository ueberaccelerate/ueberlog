#ifndef UEBERLOG_UEBERLOG_HPP
#define UEBERLOG_UEBERLOG_HPP

#include <ueberlog/logger.hpp>

#define ASSERT(condition, ...)                                          \
  ueberlog::Logger::i().throw_assert(condition, __FUNCTION__, __LINE__, \
                                     __VA_ARGS__)
#define DEBUG(...) \
  ueberlog::Logger::i().debug(__FUNCTION__, __LINE__, __VA_ARGS__)
#define INFO(...) \
  ueberlog::Logger::i().info(__FUNCTION__, __LINE__, __VA_ARGS__)
#define WARN(...) \
  ueberlog::Logger::i().warn(__FUNCTION__, __LINE__, __VA_ARGS__)
#define ERROR(...) \
  ueberlog::Logger::i().error(__FUNCTION__, __LINE__, __VA_ARGS__)

#endif  // UEBERLOG_UEBERLOG_HPP
