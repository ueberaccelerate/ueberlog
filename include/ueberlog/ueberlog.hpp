#ifndef UEBERLOG_UEBERLOG_HPP
#define UEBERLOG_UEBERLOG_HPP


#include <ueberlog/asserter.hpp>
#include <ueberlog/logger.hpp>

#define ASSERT(condition, ...) ueberlog::Asserter::i().throw_assert(condition, __FILE__, __LINE__, __VA_ARGS__)
#define DEBUG(...) ueberlog::Logger::i().debug(__FILE__, __LINE__, __VA_ARGS__)
#define INFO(...)  ueberlog::Logger::i().info (__FILE__, __LINE__, __VA_ARGS__)
#define WARN(...)  ueberlog::Logger::i().warn (__FILE__, __LINE__, __VA_ARGS__)
#define ERROR(...) ueberlog::Logger::i().error(__FILE__, __LINE__, __VA_ARGS__)

#endif // UEBERLOG_UEBERLOG_HPP
