#include <ueberlog/ueberlog.hpp>

int main() {
  DEBUG("hell: \n");
  WARN("sdasd\n");
  ERROR("asdasd\n");
  ASSERT(!false, " %d != %d\n", 42, 43);
  ASSERT(false, "hell");
  return 0;
}