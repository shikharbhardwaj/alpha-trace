//===---- buffers --------- Memory buffer definitions -----------*- C++ -*-===//
//
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Frame and z buffers
///
//===----------------------------------------------------------------------===//
#ifndef BUFFERS_ALPHA_HPP
#define BUFFERS_ALPHA_HPP

#include <cmath>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>

#include <alpha/math.hpp>

namespace alpha {
namespace buffers {

using RGB = alpha::math::Vec3<uint8_t>;

class Zbuffer {
  std::vector<float> depth_buffer;
  uint32_t width, height;

  public:
  Zbuffer() = delete;

  Zbuffer(uint32_t w, uint32_t h, float far) : width(w), height(h) {
    depth_buffer.assign(w * h, far);
  }

  void set(uint32_t x, uint32_t y, float z) {
    depth_buffer[y * width + x] = z;
  }

  float get(uint32_t x, uint32_t y) { return depth_buffer[y * width + x]; }

  void dump_as_ppm(const std::string &name) {
    std::ofstream file_h(name, std::fstream::binary);
    file_h << "P6 " << width << " " << height << " " << 255 << " ";
    for (auto elem : depth_buffer) {
      // Map range [1, 1000] to [0, 255]
      elem = (elem - 1) * 0.255f;
      uint8_t print = static_cast<uint8_t>(std::round(elem));
      file_h << print << print << print;
    }
    file_h.close();
  }
};

class Imagebuffer {
  std::unique_ptr<RGB> buffer;
  RGB* bptr;
  uint32_t width, height;

 public:
  int col_space;

  Imagebuffer() = delete;

  Imagebuffer(uint32_t w, uint32_t h, int space = 255)
    : width(w), height(h), col_space(space) {
      buffer = std::unique_ptr<RGB>(new RGB[width * height]);
      bptr = buffer.get();
    }

  void clear() {
    memset(bptr, 0, width * height * sizeof(RGB));
  }

  void set(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b) {
    bptr[y * width + x][0] = r;
    bptr[y * width + x][1] = g;
    bptr[y * width + x][2] = b;
  }

  void dump_as_ppm(const std::string &name) {
    std::ofstream file_h(name, std::fstream::binary);
    file_h << "P6 " << width << " " << height << " " << col_space << " ";
    for(auto *i = bptr; i != bptr + width * height; ++i) {
      file_h << (*i)[0] << (*i)[1] << (*i)[2];
    }
    file_h.close();
  }
};

} // namespace buffers
} // namespace alpha

#endif
