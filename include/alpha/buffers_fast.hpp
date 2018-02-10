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

class Zbuffer {
private:
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
            uint8_t print = std::round(elem);
            file_h << print << print << print;
        }
        file_h.close();
    }
};

class Imagebuffer {
private:
  std::unique_ptr<uint8_t> buffer;
  uint32_t width, height;

public:
    const int col_space = 255;

    Imagebuffer() = delete;

    Imagebuffer(uint32_t w, uint32_t h)
            : width(w), height(h) {
      buffer = std::unique_ptr<uint8_t>(new uint8_t[w * h * 3]);
      clear();
    }

    void clear() {
      memset(buffer.get(), 0, width * height * 3);
    }

    void set(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b) {
        uint8_t* bptr = buffer.get();
        bptr[y * width + 3 * x] = r;
        bptr[y * width + 3 * x + 1] = g;
        bptr[y * width + 3 * x + 2] = b;
    }

    void dump_as_ppm(const std::string &name) {
        std::ofstream file_h(name, std::fstream::binary);
        file_h << "P6 " << width << " " << height << " " << col_space << "\n";
        for(uint8_t *i = buffer.get(); i != buffer.get() + width * height * 3;
            ++i) {
          file_h << *i;
        }
        file_h.close();
    }
};

#endif
