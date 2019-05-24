#ifndef UEBERLOG_UEBERLOG_HPP
#define UEBERLOG_UEBERLOG_HPP

#include <cstdio>

#include <ueberlog/asserter.hpp>
#include <ueberlog/logger.hpp>

#define ASSERT(condition, messages...) Asserter::i().throw_assert(condition, __FILE__, __LINE__, messages)
#define DEBUG(messages...) Logger::i().debug(messages)
#define WARN(messages...) Logger::i().warn(messages)
#define ERROR(messages...) Logger::i().error(messages)

#endif // UEBERLOG_UEBERLOG_HPP
