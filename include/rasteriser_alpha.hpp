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
#include <buffers_alpha.hpp>
#include <camera_alpha.hpp>
#include <fstream>
#include <math_alpha.hpp>
#include <memory>
#include <prettyprint.hpp>
namespace alpha {
using namespace math;
class Rasteriser {
    using Point = Vec3f;

  private:
    std::unique_ptr<Framebuffer> Fbuf;
    std::unique_ptr<Zbuffer> Zbuf;
    std::shared_ptr<Camera> cam;
    int img_width, img_height;
    float far_clipping_plain;

  public:
    Rasteriser() = delete;
    Rasteriser(std::shared_ptr<Camera> cam_inst, int col_space = 255) {
        cam = std::move(cam_inst);
        img_width = cam->img_width;
        img_height = cam->img_height;
        Fbuf = std::unique_ptr<Framebuffer>(
            new Framebuffer(img_width, img_height, col_space));
        Zbuf = std::unique_ptr<Zbuffer>(
            new Zbuffer(img_width, img_height, far_clipping_plain));
    }
    void dump_as_ppm(const std::string &name) { Fbuf->dump_as_ppm(name); }
    void draw_triangle(const Point &v0, const Point &v1, const Point &v2) {
        Vec3f v0_rast, v1_rast, v2_rast;
        cam->convert_to_raster(v0, v0_rast);
        cam->convert_to_raster(v1, v1_rast);
        cam->convert_to_raster(v2, v2_rast);
#ifndef NDEBUG
        std::cout << "\nThe raster coords : " << v0_rast << " | " << v1_rast
                  << " | " << v2_rast;
#endif
        // Precompute multiplicative inverse of the z co ordinate
        v0_rast.z = 1 / v0_rast.z;
        v1_rast.z = 1 / v1_rast.z;
        v2_rast.z = 1 / v2_rast.z;
        // Compute bounding box
        float xmin = min_3(v0_rast.x, v1_rast.x, v2_rast.x);
        float ymin = min_3(v0_rast.y, v1_rast.y, v2_rast.y);
        float xmax = max_3(v0_rast.x, v1_rast.x, v2_rast.x);
        float ymax = max_3(v0_rast.y, v1_rast.y, v2_rast.y);
        if (xmin > cam->img_width - 1 || xmax < 0 ||
            ymax > cam->img_height - 1 || ymin < 0) {
            return;
        }
        uint32_t x0 = std::max(int32_t(0), (int32_t)(std::floor(xmin)));
        uint32_t y0 = std::max(int32_t(0), (int32_t)(std::floor(ymin)));
        uint32_t x1 =
            std::max(int32_t(img_width) - 1, (int32_t)(std::floor(xmax)));
        uint32_t y1 =
            std::max(int32_t(img_height) - 1, (int32_t)(std::floor(ymin)));
        float total_area_inv = 1 / edge_function(v0_rast, v1_rast, v2_rast);
        std::cout << "Total area : " << 1 / total_area_inv;
        for (uint32_t y = y0; y <= y1; y++) {
            for (uint32_t x = x0; x <= x1; x++) {
                Vec3f pixel_sample(x + 0.5f, y + 0.5f, 0);
                float w0 = edge_function(v1_rast, v2_rast, pixel_sample);
                float w1 = edge_function(v2_rast, v0_rast, pixel_sample);
                float w2 = edge_function(v0_rast, v1_rast, pixel_sample);
                if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
                    w0 *= total_area_inv;
                    w1 *= total_area_inv;
                    w2 *= total_area_inv;
                    // Compute correct interpolation
                    float z_inv =
                        v0_rast.z * w0 + v1_rast.z * w1 + v2_rast.z * w2;
                    float z = 1 / z_inv;
                    if (z < Zbuf->get(x, y)) {
                        Zbuf->set(x, y, z);
                    }
                    Fbuf->set(x, y, 255 * w0, 255 * w1, 255 * w2);
                }
            }
        }
    }
};
}
#endif
