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
  std::unique_ptr<float> depth_buffer;
  uint32_t width, height;
  float far;

  public:
  Zbuffer() = delete;

  Zbuffer(uint32_t w, uint32_t h, float far) : width(w), height(h), far(far) {
    depth_buffer = std::unique_ptr<float>(new float[w * h]);
    for(uint32_t i = 0; i < width * height; ++i)
      depth_buffer.get()[i] = far;
  }

  void clear() {
      std::fill(depth_buffer.get(), depth_buffer.get() + width * height, far);
  }

  void set(uint32_t x, uint32_t y, float z) {
    depth_buffer.get()[y * width + x] = z;
  }

  float get(uint32_t x, uint32_t y) {
    return depth_buffer.get()[y * width + x];
  }

  void dump_as_ppm(const std::string &name) {
    std::ofstream file_h(name, std::fstream::binary);
    file_h << "P6 " << width << " " << height << " " << 255 << " ";
    for (uint32_t i = 0; i < width * height; ++i) {
      // Map range [1, 1000] to [0, 255]
      float elem = depth_buffer.get()[i];
      elem = (elem - 1) * 0.255f;
      uint8_t print = static_cast<uint8_t>(std::round(elem));
      file_h << print << print << print;
    }
    file_h.close();
  }
};

class Imagebuffer {
  std::unique_ptr<RGB> buffer;
  uint32_t width, height;

 public:
  int col_space;

  Imagebuffer() = delete;

  Imagebuffer(uint32_t w, uint32_t h, int space = 255)
    : width(w), height(h), col_space(space) {
      buffer = std::unique_ptr<RGB>(new RGB[width * height]);
    }

  void clear() {
    memset(buffer.get(), 0, width * height * sizeof(RGB));
  }

  void set(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b) {
    buffer.get()[y * width + x][0] = r;
    buffer.get()[y * width + x][1] = g;
    buffer.get()[y * width + x][2] = b;
  }

  RGB& get(int x, int y) {
    return buffer.get()[y * width + x];
  }

  void dump_to_stream(std::ostream& ss) {
    // std::ofstream file_h(name, std::fstream::binary);
    ss << "P6 " << width << " " << height << " " << col_space << " ";
    for(auto *i = buffer.get(); i != buffer.get() + width * height; ++i) {
      ss << (*i)[0] << (*i)[1] << (*i)[2];
    }
  }

  void dump_as_ppm(const std::string &name) {
    std::ofstream file_h(name, std::fstream::binary);
    file_h << "P6 " << width << " " << height << " " << col_space << " ";
    for(auto *i = buffer.get(); i != buffer.get() + width * height; ++i) {
      file_h << (*i)[0] << (*i)[1] << (*i)[2];
    }
    file_h.close();
  }
};

} // namespace buffers
} // namespace alpha

#endif
