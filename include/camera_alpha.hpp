//===---- camera ------- Camera abstraction definitions --------*- C++ -*-===//
////
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Implements a pinhole camera model
///
///
//===----------------------------------------------------------------------===//
#ifndef CAMERA_ALPHA_HPP
#define CAMERA_ALPHA_HPP
#include <iostream>
#include <math_alpha.hpp>
namespace alpha {
namespace camera {
using namespace math;
static const float inch_to_mm = 25.4;
enum class fit_resolution_gate { Fill = 0, Overscan };
void compute_screen_coordinates(const float film_aperture_width,
                                const float film_aperture_height,
                                const uint32_t img_width,
                                const uint32_t img_height,
                                const fit_resolution_gate &fit_setting,
                                const float near_clipping_plain,
                                const float focal_length, float &top,
                                float &bottom, float &left, float &right) {
    // Implements a pinhole camera model
    float film_aspect_ratio = film_aperture_width / film_aperture_height;
    float device_aspect_ratio = img_width / (float)img_height;
    top = ((film_aperture_height * inch_to_mm) / 2 / focal_length) *
          near_clipping_plain;
    right = ((film_aperture_width * inch_to_mm) / 2 / focal_length) *
            near_clipping_plain;
#ifndef NDEBUG
    float fov = 2 * 180 / M_PI * atan((right / near_clipping_plain));
    std::cout << "Field of view : " << fov << std::endl;
#endif
    float xscale = 1, yscale = 1;
    switch (fit_setting) {
    case fit_resolution_gate::Fill:
        if (device_aspect_ratio < film_aspect_ratio) {
            xscale = device_aspect_ratio / film_aspect_ratio;
        } else {
            yscale = film_aspect_ratio / device_aspect_ratio;
        }
        break;
    case fit_resolution_gate::Overscan:
        if (device_aspect_ratio < film_aspect_ratio) {
            yscale = film_aspect_ratio / device_aspect_ratio;
        } else {
            xscale = device_aspect_ratio / film_aspect_ratio;
        }
    }
    right *= xscale;
    top *= yscale;
    bottom = -top;
    left = -right;
}
void convert_to_raster(const Vec3f &v_world, const Matrix44f &world_to_cam,
                       const float t, const float b, const float l,
                       const float r, const float near, const float img_width,
                       const float img_height, Vec3f &raster) {
    Vec3f v_cam;
    world_to_cam.mult_vec_matrix(v_world, v_cam);
    // Convert to screen space
    // Perform perspective divide
    Vec2f v_screen;
    v_screen.x = near * v_cam.x / -v_cam.z;
    v_screen.y = near * v_cam.y / -v_cam.z;
    // Convert to NDC
    Vec2f v_NDC;
    v_NDC.x = 2 * v_screen.x / (r - l) - (r + l) / (r - l);
    v_NDC.y = 2 * v_screen.y / (t - b) - (t + b) / (t - b);
    // Convert to raster space
    raster.x = (v_NDC.x + 1) / 2 * img_width;
    raster.y = (1 - v_NDC.y) / 2 * img_height;
    raster.z = -v_cam.z;
}
}
}
#endif
