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
#include <math_alpha.hpp>
#include <prettyprint.hpp>
namespace alpha {
using rgb = Vec3i;
using Point = Vec2f;
class Framebuffer {
    std::vector<std::vector<rgb>> buffer;
    uint32_t width, height;

  public:
    int col_space;
    Framebuffer() = delete;
    Framebuffer(uint32_t w, uint32_t h, int space)
        : width(w), height(h), col_space(space) {
        buffer.assign(height, {});
        for (auto &elem : buffer) {
            elem.assign(width, {});
        }
    }
    void set(uint32_t x, uint32_t y, rgb color) { buffer[y][x] = color; }
    void dump_as_ppm(const std::string &name) {
        auto file_h = fopen(name.c_str(), "w");
        fprintf(file_h, "P6\n%lu\n%lu\n%d\n", (size_t)width, (size_t)height,
                col_space);
        for (auto &row : buffer) {
            for (auto elem : row) {
                fprintf(file_h, "%c%c%c", elem.x, elem.y, elem.z);
            }
        }
        fclose(file_h);
    }
};
class Rasteriser {
    std::unique_ptr<Framebuffer> buf;
    uint32_t screen_width, screen_height;
    float edge_function(const Point &a, const Point &b, const Point &c) {
        return ((b.y - a.y) * (c.x - a.x) - (b.x - a.x) * (c.y - a.y));
    }
    std::pair<Point, Point> compute_bounding_box(const Point &a, const Point &b,
                                                 const Point &c) {
        float min_x = min_3(a.x, b.x, c.x);
        float min_y = min_3(a.y, b.y, c.y);
        float max_x = max_3(a.x, b.x, c.x);
        float max_y = max_3(a.y, b.y, c.y);
        // Keep in screen bounds
        min_x = std::max(min_x, 0.f);
        min_y = std::max(min_y, 0.f);
        max_x = std::min(max_x, screen_width - 1.f);
        max_y = std::min(max_y, screen_height - 1.f);
        return std::make_pair(Point(min_x, min_y), Point(max_x, max_y));
    }

  public:
    Rasteriser() = delete;
    Rasteriser(uint32_t w, uint32_t h, int col_space = 255)
        : screen_width(w), screen_height(h) {
        buf = std::unique_ptr<Framebuffer>(
            new Framebuffer(screen_width, screen_height, col_space));
    }
    void dump_as_ppm(const std::string &name) { buf->dump_as_ppm(name); }
    void draw_triangle(const Point &v0, const Point &v1, const Point &v2) {
        auto bbox = compute_bounding_box(v0, v1, v2);
        auto total_area = edge_function(v0, v1, v2);
        std::cout << "Total area : " << total_area;
        // Computing the barycentric co-ordinates for colour contribution
        for (uint32_t i = bbox.first.y; i <= bbox.second.y; i++) {
            for (uint32_t j = bbox.first.x; j <= bbox.second.x; j++) {
                Point p(j + 0.5f, i + 0.5f);
                float w0 = edge_function(v1, v2, p);
                float w1 = edge_function(v2, v0, p);
                float w2 = edge_function(v0, v1, p);
                // If p is visible, render
                if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
                    w0 /= total_area;
                    w1 /= total_area;
                    w2 /= total_area;
                    buf->set(j, i, rgb(w0 * buf->col_space, w1 * buf->col_space,
                                       w2 * buf->col_space));
                }
            }
        }
    }
};
}
#endif
