#ifndef UEBERLOG_UEBERLOG_HPP
#define UEBERLOG_UEBERLOG_HPP


#include <ueberlog/asserter.hpp>
#include <ueberlog/logger.hpp>

#define ASSERT(condition, messages...) ueberlog::Asserter::i().throw_assert(condition, __FILE__, __LINE__, messages)
#define DEBUG(messages...) ueberlog::Logger::i().debug(__FILE__, __LINE__, messages)
#define INFO(messages...)  ueberlog::Logger::i().info(messages)
#define WARN(messages...)  ueberlog::Logger::i().warn(__FILE__, __LINE__, messages)
#define ERROR(messages...) ueberlog::Logger::i().error(__FILE__, __LINE__, messages)

#endif // UEBERLOG_UEBERLOG_HPP
