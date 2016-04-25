//===--- graphics.hpp --- Math abstraction definitions ----------*- C++ -*-===//
//
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
///
/// Implement a rasterisation algorithm
///
//===----------------------------------------------------------------------===//
#ifndef RASTERISER_ALPHA_HPP
#define RASTERISER_ALPHA_HPP
#include <memory>
#include <fstream>
#include <math_alpha.hpp>
#include <prettyprint.hpp>
namespace alpha {
using rgb = Vec3<uint8_t>;
using Point = Vec2i;
class Framebuffer {
    std::vector<std::vector<uint8_t>> buffer;
    uint32_t width, height;

  public:
    int col_space;
    Framebuffer() = delete;
    Framebuffer(uint32_t w, uint32_t h, int space)
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
class Rasteriser {
    std::unique_ptr<Framebuffer> buf;
    inline int edge_function(const Point &a, const Point &b, const Point &c) {
        return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    }
    int screen_width, screen_height;

  public:
    Rasteriser() = delete;
    Rasteriser(uint32_t w, uint32_t h, int col_space = 255)
        : screen_width(w), screen_height(h) {
        buf = std::unique_ptr<Framebuffer>(
            new Framebuffer(screen_width, screen_height, col_space));
    }
    void dump_as_ppm(const std::string &name) { buf->dump_as_ppm(name); }
    void draw_triangle(const Point &v0, const Point &v1, const Point &v2) {
        const int min_x = std::max(min_3(v0.x, v1.x, v2.x), 0);
        const int min_y = std::max(min_3(v0.y, v1.y, v2.y), 0);
        const int max_x = std::min(max_3(v0.x, v1.x, v2.x), screen_width - 1);
        const int max_y = std::min(max_3(v0.y, v1.y, v2.y), screen_height - 1);
        // Keep in screen bounds
        const float total_area = edge_function(v0, v1, v2);
        const float mult = buf->col_space / total_area;
        // Computing the barycentric co-ordinates for colour contribution
        // Triangle setup
        // Convention : Anticlockwise winding
        const int a01 = v0.y - v1.y, b01 = v1.x - v0.x;
        const int a12 = v1.y - v2.y, b12 = v2.x - v1.x;
        const int a20 = v2.y - v0.y, b20 = v0.x - v2.x;
        int w0_row = edge_function(v0, v1, {min_x, min_y});
        int w1_row = edge_function(v1, v2, {min_x, min_y});
        int w2_row = edge_function(v2, v0, {min_x, min_y});
        int w0, w1, w2;
        int x, y;
        auto &buf_ref = *buf;
        for (y = min_y; y <= max_y; y++) {
            w0 = w0_row;
            w1 = w1_row;
            w2 = w2_row;
            for (x = min_x; x <= max_x; x++) {
                if ((w1 | w2 | w0) >= 0) {
                    // If visible, render
                    buf_ref.set(x, y, w0 * mult, w1 * mult, w2 * mult);
                }
                w0 += a01;
                w1 += a12;
                w2 += a20;
            }
            w0_row += b01;
            w1_row += b12;
            w2_row += b20;
        }
    }
};
}
#endif
