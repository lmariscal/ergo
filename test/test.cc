#include <ergo/types.hh>
#include <iostream>

using namespace ergo;

i32 main() {
  std::cout << "Hi there\n";

  b8 x = true;
  if (x) {
    std::cout << "x is true\n";
  } else {
    std::cout << "x is false\n";
  }

  b32 y = true;
  if (y) {
    std::cout << "y is true\n";
  } else {
    std::cout << "y is false\n";
  }

  if (x == y) {
    std::cout << "x == y\n";
  } else {
    std::cout << "x != y\n";
  }

  return 0;
}
