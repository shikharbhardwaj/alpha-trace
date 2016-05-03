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
    std::unique_ptr<Framebuffer> Ibuf;
    std::unique_ptr<Zbuffer> Zbuf;
    std::shared_ptr<Camera> cam;
    inline float edgeFunction(const Vec3f &a, const Vec3f &b, const Vec3f &c) {
        return (c[0] - a[0]) * (b[1] - a[1]) - (c[1] - a[1]) * (b[0] - a[0]);
    }
    int screen_width, screen_height;
    float far_clipping_plain;

  public:
    Rasteriser() = delete;
    Rasteriser(uint32_t w, uint32_t h, std::shared_ptr<Camera> cam_inst,
               int col_space = 255)
        : screen_width(w), screen_height(h) {
        Ibuf = std::unique_ptr<Framebuffer>(
            new Framebuffer(screen_width, screen_height, col_space));
        Zbuf = std::unique_ptr<Zbuffer>(
            new Zbuffer(screen_width, screen_height, far_clipping_plain));
        cam = cam_inst;
    }
    void dump_as_ppm(const std::string &name) { Ibuf->dump_as_ppm(name); }
};
}
#endif
