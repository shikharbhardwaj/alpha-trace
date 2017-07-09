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
#include <fstream>
#include <iostream>
#include <vector>

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
            uint8_t print = std::round(elem);
            file_h << print << print << print;
        }
        file_h.close();
    }
};

class Imagebuffer {
    std::vector<std::vector<uint8_t>> buffer;
    uint32_t width, height;

public:
    int col_space;

    Imagebuffer() = delete;

    Imagebuffer(uint32_t w, uint32_t h, int space)
            : width(w), height(h), col_space(space) {
        buffer.assign(height, {});
        for (auto &elem : buffer) {
            elem.assign(3 * width, 0);
        }
    }

    void set(uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b) {
        buffer[y][3 * x] = r;
        buffer[y][3 * x + 1] = g;
        buffer[y][3 * x + 2] = b;
    }

    void dump_as_ppm(const std::string &name) {
        std::ofstream file_h(name, std::fstream::binary);
        file_h << "P6 " << width << " " << height << " " << col_space << " ";
        for (auto &row : buffer) {
            for (auto elem : row) {
                file_h << elem;
            }
        }
        file_h.close();
    }
};

#endif
