# ueberlog
A simple logger and assert library. header only

![alt text](https://github.com/ueberaccelerate/ueberlog/blob/master/doc/output.png)


## Installation

Use with cmake:

```cmake
add_subdirectory(ueberlog)
target_link_libraries ( <YOUR_TARGER> PUBLIC ueberlog )
```
Console version:
```bash
g++ -std=c++17 -Iueberlog/include main.cpp 
```

## Usage

```c++
#include <ueberlog/ueberlog.hpp>  

int main() {
  DEBUG("HELP %d %f\n", 42, 3.14f);
  INFO("HELP %d %f\n", 42, 3.14f);
  ERROR("HELP %d %f\n", 42, 3.14f);
  WARN("HELP %d %f\n", 42, 3.14f);
  ASSERT(false, " %d != %d\n", 42, 43);
  return 0;
}
```
