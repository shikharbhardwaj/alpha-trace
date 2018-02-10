#include <iostream>
#include <alpha/buffers.hpp>

using namespace alpha;
using namespace alpha::buffers;

int main() {
  Imagebuffer test(1024, 768);
  for(int i = 0; i < 1024; ++i) {
    for(int j = 0; j < 768; ++j) {
      test.set(i, j, 255, 0, 0);
    }
  }

  test.dump_as_ppm("white.ppm");
}
