//===---- rasteriser ------- Rasterisation routines -------------*- C++ -*-===//
//
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Implement a rasterisation algorithm
///
//===----------------------------------------------------------------------===//
#ifndef RASTERISER_ALPHA_HPP
#define RASTERISER_ALPHA_HPP

#include <fstream>
#include <memory>

#include "math.hpp"
#include "buffers.hpp"
#include "camera.hpp"

namespace alpha {
namespace shaders {
struct do_nothing {
    using RGB = math::Vec3f;

    RGB operator()(float b0, float b1, float b2, float z, math::Vec3f v0_cam,
                   math::Vec3f v1_cam, math::Vec3f v2_cam) {
        (void) b0;
        (void) b1;
        (void) b2;
        (void) z;
        (void) v0_cam;
        (void) v1_cam;
        (void) v2_cam;
        return RGB(0, 0, 0);
    }
};
}
template<typename Shader = shaders::do_nothing>
class Rasteriser {
    using Point = math::Vec3f;
    using RGB = math::Vec3f;

private:
    std::unique_ptr<Imagebuffer> Fbuf;
    std::unique_ptr<Zbuffer> Zbuf;
    std::shared_ptr<Camera> cam;
    Shader render_triangle;
    int width, height;

public:
    Rasteriser() = delete;

    Rasteriser(std::shared_ptr<Camera> cam_inst, Shader f = Shader(),
               int col_space = 255) {
        cam = std::move(cam_inst);
        render_triangle = std::move(f);
        width = cam->img_width;
        height = cam->img_height;
        Fbuf = std::unique_ptr<Imagebuffer>(
                new Imagebuffer(width, height, col_space));
        Zbuf = std::unique_ptr<Zbuffer>(
                new Zbuffer(width, height, cam->get_far_clipping_plain()));
    }

    void dump_as_ppm(const std::string &name) { Fbuf->dump_as_ppm(name); }

    void dump_zbuf(const std::string &name) { Zbuf->dump_as_ppm(name); }

    bool draw_triangle(const Point &v0, const Point &v1, const Point &v2) {
        // TODO : Optimize
        Point v0_rast, v1_rast, v2_rast, v0_cam, v1_cam, v2_cam;
        cam->convert_to_raster(v0, v0_rast, v0_cam);
        cam->convert_to_raster(v1, v1_rast, v1_cam);
        cam->convert_to_raster(v2, v2_rast, v2_cam);
#ifdef ALPHA_DEBUG
        std::cout << "\nThe raster coords : " << v0_rast << " | " << v1_rast
                  << " | " << v2_rast;
#endif
        // Precompute multiplicative inverse of the z co ordinate
        v0_rast[2] = 1 / v0_rast[2];
        v1_rast[2] = 1 / v1_rast[2];
        v2_rast[2] = 1 / v2_rast[2];
        // Compute bounding box
        float xmin = math::min_3(v0_rast[0], v1_rast[0], v2_rast[0]);
        float ymin = math::min_3(v0_rast[1], v1_rast[1], v2_rast[1]);
        float xmax = math::max_3(v0_rast[0], v1_rast[0], v2_rast[0]);
        float ymax = math::max_3(v0_rast[1], v1_rast[1], v2_rast[1]);
        if (xmin > width - 1 || xmax < 0 || ymax > height - 1 || ymin < 0) {
#ifdef ALPHA_DEBUG
            std::cout << "\nTriangle not present";
#endif
            return false;
        }
        typedef int32_t i32t;
        uint32_t x0 = std::max(i32t(0), (i32t) (std::floor(xmin)));
        uint32_t y0 = std::max(i32t(0), (i32t) (std::floor(ymin)));
        uint32_t x1 = std::min(i32t(width) - 1, (i32t) (std::floor(xmax)));
        uint32_t y1 = std::min(i32t(height) - 1, (i32t) (std::floor(ymax)));

        float total_area_inv = 1 / math::edge_function(v0_rast, v1_rast, v2_rast);
#ifdef ALPHA_DEBUG
        std::cout << "Total area : " << 1 / total_area_inv;
#endif
        if (total_area_inv < 0.f) {
            // We do not render negative area triangles
            return false;
        }
        // Triangle setup
        float a01 = v0_rast[1] - v1_rast[1], b01 = v1_rast[0] - v0_rast[0];
        float a12 = v1_rast[1] - v2_rast[1], b12 = v2_rast[0] - v1_rast[0];
        float a20 = v2_rast[1] - v0_rast[1], b20 = v0_rast[0] - v2_rast[0];
        // Computing the Barycentric co-ords at minX, minY
        Point p = {float(x0) + 0.5f, float(y0) + 0.5f, 0.f};
        float w0_row = math::edge_function(v1_rast, v2_rast, p);
        float w1_row = math::edge_function(v2_rast, v0_rast, p);
        float w2_row = math::edge_function(v0_rast, v1_rast, p);
        // The inner loop
        for (uint32_t y = y0; y <= y1; y++) {
            float w0 = w0_row;
            float w1 = w1_row;
            float w2 = w2_row;
            for (uint32_t x = x0; x <= x1; x++) {
#ifdef ALPHA_DEBUG
                std::cout << Point(w0, w1, w2) << " : " << math::Vec2i(x, y)
                          << std::endl;
                std::cin.get();
#endif
                if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
                    float b0 = w0 * total_area_inv;
                    float b1 = w1 * total_area_inv;
                    float b2 = w2 * total_area_inv;
                    // Compute correct interpolation
                    float z_inv =
                            v0_rast[2] * b0 + v1_rast[2] * b1 + v2_rast[2] * b2;
                    float z = 1 / z_inv;
                    if (z < Zbuf->get(x, y)) {
                        // Yay! Render
                        Zbuf->set(x, y, z);
                        auto col = render_triangle(b0, b1, b2, z, v0_cam,
                                                   v1_cam, v2_cam);
                        Fbuf->set(x, y, col[0], col[1], col[2]);
                    }
                }
                w0 -= a12;
                w1 -= a20;
                w2 -= a01;
            }
            w0_row -= b12;
            w1_row -= b20;
            w2_row -= b01;
        }
        return true;
    }

    void draw_triangle_16xAA(const Point &v0, const Point &v1,
                             const Point &v2) {
        // TODO: Optimize
        Point v0_rast, v1_rast, v2_rast, v0_cam, v1_cam, v2_cam;
        cam->convert_to_raster(v0, v0_rast, v0_cam);
        cam->convert_to_raster(v1, v1_rast, v1_cam);
        cam->convert_to_raster(v2, v2_rast, v2_cam);
#ifdef ALPHA_DEBUG
        std::cout << "\nThe raster coords : " << v0_rast << " | " << v1_rast
                  << " | " << v2_rast;
#endif
        // Precompute multiplicative inverse of the z co ordinate
        v0_rast[2] = 1 / v0_rast[2];
        v1_rast[2] = 1 / v1_rast[2];
        v2_rast[2] = 1 / v2_rast[2];
        // Compute bounding box
        float xmin = math::min_3(v0_rast[0], v1_rast[0], v2_rast[0]);
        float ymin = math::min_3(v0_rast[1], v1_rast[1], v2_rast[1]);
        float xmax = math::max_3(v0_rast[0], v1_rast[0], v2_rast[0]);
        float ymax = math::max_3(v0_rast[1], v1_rast[1], v2_rast[1]);
        if (xmin > width - 1 || xmax < 0 || ymax > height - 1 || ymin < 0) {
#ifdef ALPHA_DEBUG
            std::cout << "\nTriangle not present";
#endif
            return;
        }
        typedef int32_t i32t;
        uint32_t x0 = std::max(i32t(0), (i32t) (std::floor(xmin)));
        uint32_t y0 = std::max(i32t(0), (i32t) (std::floor(ymin)));
        uint32_t x1 = std::min(i32t(width) - 1, (i32t) (std::floor(xmax)));
        uint32_t y1 = std::min(i32t(height) - 1, (i32t) (std::floor(ymax)));

        float total_area_inv = 1 / math::edge_function(v0_rast, v1_rast, v2_rast);
#ifdef ALPHA_DEBUG
        std::cout << "Total area : " << 1 / total_area_inv;
#endif
        // Triangle setup
        float a01 = v0_rast[1] - v1_rast[1], b01 = v1_rast[0] - v0_rast[0];
        float a12 = v1_rast[1] - v2_rast[1], b12 = v2_rast[0] - v1_rast[0];
        float a20 = v2_rast[1] - v0_rast[1], b20 = v0_rast[0] - v2_rast[0];
        // Computing the Barycentric co-ords at minX, minY
        Point p = {float(x0) + 0.5f, float(y0) + 0.5f, 0.f};
        float w0_row = math::edge_function(v1_rast, v2_rast, p);
        float w1_row = math::edge_function(v2_rast, v0_rast, p);
        float w2_row = math::edge_function(v0_rast, v1_rast, p);
        // The inner loop
        for (uint32_t y = y0; y <= y1; y++) {
            float w0 = w0_row;
            float w1 = w1_row;
            float w2 = w2_row;
            for (uint32_t x = x0; x <= x1; x++) {
#ifdef ALPHA_DEBUG
                std::cout << Point(w0, w1, w2) << " : " << math::Vec2i(x, y)
                          << std::endl;
                std::cin.get();
#endif
                if (w0 >= 0 && w1 >= 0 && w2 >= 0) {

                    float z_inv = v0_rast[2] * w0 * total_area_inv +
                                  v1_rast[2] * w1 * total_area_inv +
                                  v2_rast[2] * w2 * total_area_inv;
                    float z = 1 / z_inv;
                    if (z < Zbuf->get(x, y)) {
                        Zbuf->set(x, y, z);
                        std::vector<Point> pixel_samples(16);
                        // Use 16 samples per pixel
                        pixel_samples[0][0] = w0 + 3.0 / 8 * a12 + 3.0 / 8 * b12;
                        pixel_samples[0][1] = w1 + 3.0 / 8 * a20 + 3.0 / 8 * b20;
                        pixel_samples[0][2] = w2 + 3.0 / 8 * a01 + 3.0 / 8 * b01;
                        for (int i = 1; i < 4; i++) {
                            pixel_samples[4 * i][0] =
                                    pixel_samples[4 * (i - 1)][0] - 0.25 * b12;
                            pixel_samples[4 * i][1] =
                                    pixel_samples[4 * (i - 1)][1] - 0.25 * b20;
                            pixel_samples[4 * i][2] =
                                    pixel_samples[4 * (i - 1)][2] - 0.25 * b01;
                        }
                        for (int i = 0; i < 4; i++) {
                            for (int j = 1; j < 4; j++) {
                                pixel_samples[4 * i + j][0] =
                                        pixel_samples[4 * i + j - 1][0] - 0.25 * a12;
                                pixel_samples[4 * i + j][1] =
                                        pixel_samples[4 * i + j - 1][1] - 0.25 * a20;
                                pixel_samples[4 * i + j][2] =
                                        pixel_samples[4 * i + j - 1][2] - 0.25 * a01;
                            }
                        }
                        float b0 = w0, b1 = w1, b2 = w2;
                        RGB total_color = {0, 0, 0};
                        for (auto elem : pixel_samples) {
                            b0 = elem[0], b1 = elem[1], b2 = elem[2];
                            b0 *= total_area_inv;
                            b1 *= total_area_inv;
                            b2 *= total_area_inv;
                            auto col = render_triangle(b0, b1, b2, z, v0_cam,
                                                       v1_cam, v2_cam);
                            total_color = total_color + col;
                        }
                        Fbuf->set(x, y, total_color[0] / 16, total_color[1] / 16,
                                  total_color[2] / 16);
                    }
                }
                w0 -= a12;
                w1 -= a20;
                w2 -= a01;
            }
            w0_row -= b12;
            w1_row -= b20;
            w2_row -= b01;
        }
    }
};
}
#endif
