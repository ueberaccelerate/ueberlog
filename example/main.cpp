#include <ueberlog/ueberlog.hpp>

int main() {
  DEBUG("HELP\n");
  WARN("sdasd\n");
  INFO("info label\n");
  ERROR("asdasd: %d\n", 42);
  ASSERT(false, " %d != %d\n", 42, 43);
//  ASSERT(false, "hell");
  return 0;
}
