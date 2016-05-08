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
enum class fit_resolution_gate { Fill = 0, Overscan };
class Camera {

  private:
    float inch_to_mm = 25.4f;
    float film_aperture_width, film_aperture_height;
    fit_resolution_gate fit_setting;
    float near_clipping_plain, far_clipping_plain;
    float focal_length;
    float top, bottom, left, right;
    math::Matrix44f world_to_cam;

  public:
    uint32_t img_width, img_height;
    Camera() = delete;
    Camera(uint32_t width, uint32_t height, float fa_w, float fa_h,
           float z_near, float z_far, float f_length, math::Matrix44f w2cam)
        : film_aperture_width(fa_w), film_aperture_height(fa_h),
          near_clipping_plain(z_near), far_clipping_plain(z_far),
          focal_length(f_length), world_to_cam(w2cam), img_width(width),
          img_height(height) {
        fit_setting = fit_resolution_gate::Overscan;
        compute_screen_coordinates();
    }
    float get_far_clipping_plain() { return far_clipping_plain; }
    void compute_screen_coordinates() {
        // Implements a pinhole camera model
        float film_aspect_ratio = film_aperture_width / film_aperture_height;
        float device_aspect_ratio = img_width / (float)img_height;
        top = ((film_aperture_height * inch_to_mm) / 2 / focal_length) *
              near_clipping_plain;
        right = ((film_aperture_width * inch_to_mm) / 2 / focal_length) *
                near_clipping_plain;
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
#ifdef ALPHA_DEBUG
        float fov = 2 * 180 / M_PI * atan((right / near_clipping_plain));
        std::cout << "Field of view : " << fov << std::endl;
        std::cout << "Screen co-ords : " << top << "x" << right << std::endl;
        std::cout << "Img_dims" << img_width << "x" << img_height << std::endl;
#endif
    }
    void convert_to_raster(const math::Vec3f &v_world, math::Vec3f &raster,
                           math::Vec3f &v_cam) {
#ifdef ALPHA_DEBUG
        std::cout << "\nWorld co-ords" << v_world;
#endif
        world_to_cam.mult_vec_matrix(v_world, v_cam);
#ifdef ALPHA_DEBUG
        std::cout << "\nCam co-ords" << v_cam;
#endif
        // Convert to screen space
        // Perform perspective divide
        math::Vec2f v_screen;
        v_screen.x = near_clipping_plain * v_cam.x / -v_cam.z;
        v_screen.y = near_clipping_plain * v_cam.y / -v_cam.z;
#ifdef ALPHA_DEBUG
        std::cout << "\nScreen co-ordinates : " << v_screen;
#endif
        // Convert to NDC
        math::Vec2f v_NDC;
        v_NDC.x =
            2 * v_screen.x / (right - left) - (right + left) / (right - left);
        v_NDC.y =
            2 * v_screen.y / (top - bottom) - (top + bottom) / (top - bottom);
        // Convert to raster space
        raster.x = (v_NDC.x + 1) / 2 * img_width;
        raster.y = (1 - v_NDC.y) / 2 * img_height;
        raster.z = -v_cam.z;
    }
};
}
#endif
