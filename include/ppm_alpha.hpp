//===---- ppm.hpp ----- PPM image abstraction definitions -------*- C++ -*-===//
//
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Consists of a simple abstraction over the PPM image format
///
///
//===----------------------------------------------------------------------===//
#ifndef PPM_ALPHA
#define PPM_ALPHA
#include <cstdio>
#include <vector>
#include <math_alpha.hpp>
namespace alpha {
class ppm_image {
  private:
    using rgb = alpha::Vec3<int>;
    std::string name;
    size_t height, width;
    std::vector<std::vector<rgb>> content;

  public:
    ppm_image() = delete;
    ppm_image(const std::string &nm, size_t h, size_t w)
        : name(nm), height(h), width(w) {
        content.resize(h);
        for (auto &elem : content) {
            elem.assign(w, rgb(0, 0, 0));
        }
    }
    void set(size_t x, size_t y, rgb color) { content[y][x] = color; }
    void dump() {
        auto file_h = fopen(name.c_str(), "w");
        std::string header = "P6 ";
        header +=
            std::to_string(width) + " " + std::to_string(height) + " 255 ";
        fprintf(file_h, "%s", header.c_str());
        for (auto &row : content) {
            for (auto elem : row) {
                fprintf(file_h, "%c%c%c", elem.x, elem.y, elem.z);
            }
        }
        fclose(file_h);
    }
};
}
#endif
