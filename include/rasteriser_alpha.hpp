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
        return (c.x * (a.y - b.y) + c.y * (b.x - a.x) + a.x * b.y - a.y - b.x);
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
        // Computing the barycentric co-ordinates for colour contribution
        // Triangle setup
        float a01 = v0.y - v1.y, b01 = v1.x - v0.x;
        float a12 = v1.y - v2.y, b12 = v2.x - v1.x;
        float a20 = v2.y - v0.y, b20 = v0.x - v2.x;
        Point p(bbox.first.x, bbox.first.y);
        float w0_row = edge_function(v1, v2, p);
        float w1_row = edge_function(v2, v0, p);
        float w2_row = edge_function(v0, v1, p);
        for (; p.y <= bbox.second.y; p.y++) {
            float w0 = w0_row;
            float w1 = w1_row;
            float w2 = w2_row;
            for (p.x = bbox.first.x; p.x <= bbox.second.x; p.x++) {
                if ((w1 | w2 | w3) >= 0) {
                    // If p is visible, render
                    buf->set(p.x, p.y, rgb(w0 * buf->col_space / total_area,
                                           w1 * buf->col_space / total_area,
                                           w2 * buf->col_space / total_area));
                }
                w0 += a12;
                w1 += a20;
                w2 += a01;
            }
            w0_row += b12;
            w1_row += b20;
            w2_row += b01;
        }
    }
};
}
#endif
