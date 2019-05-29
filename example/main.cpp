#include <ueberlog/ueberlog.hpp>

int main() {
  DEBUG("HELP %d %f\n", 42, 3.14f);
  INFO("HELP %d %f\n", 42, 3.14f);
  ERROR("HELP %d %f\n", 42, 3.14f);
  WARN("HELP %d %f\n", 42, 3.14f);
  ASSERT(false, " %d != %d\n", 42, 43);

  return 0;
}
