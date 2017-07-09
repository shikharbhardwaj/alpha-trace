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

#include <cassert>
#include <fstream>
#include <iostream>

#include <alpha/math_alpha.hpp>

namespace alpha {
enum class fit_resolution_gate {
    Fill = 0, Overscan
};

class Camera {

private:
    float inch_to_mm = 25.4f;
    float film_aperture_width, film_aperture_height;
    fit_resolution_gate fit_setting;
    float near_clipping_plain, far_clipping_plain;
    float focal_length;
    float top, bottom, left, right, fov;
    math::Matrix44f world_to_cam;
    math::Matrix44f M_proj;

public:
    uint32_t img_width, img_height;

    Camera() = delete;

    Camera(const std::string &file_name, bool column_major = false) {
        // Import settings from a file
        std::ifstream handle(file_name);
        handle >> img_width >> img_height >> film_aperture_width >>
               film_aperture_height >> near_clipping_plain >> far_clipping_plain >>
               focal_length;
        if (column_major) {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    handle >> world_to_cam[j][i];
                }
            }
        } else {
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    handle >> world_to_cam[i][j];
                }
            }
        }
        int i;
        handle >> i;
        if (i == 0) {
            fit_setting = fit_resolution_gate::Overscan;
        } else {
            fit_setting = fit_resolution_gate::Fill;
        }
        compute_screen_coordinates();
    }

    Camera(uint32_t width, uint32_t height, float fa_w, float fa_h,
           float z_near, float z_far, float f_length, math::Matrix44f w2cam,
           fit_resolution_gate setting = fit_resolution_gate::Overscan)
            : film_aperture_width(fa_w), film_aperture_height(fa_h),
              near_clipping_plain(z_near), far_clipping_plain(z_far),
              focal_length(f_length), world_to_cam(w2cam), img_width(width),
              img_height(height) {
        fit_setting = setting;
        compute_screen_coordinates();
    }

    float get_far_clipping_plain() { return far_clipping_plain; }

    void compute_screen_coordinates() {
        // Implements a pinhole camera model
        float film_aspect_ratio = film_aperture_width / film_aperture_height;
        float device_aspect_ratio = img_width / (float) img_height;
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

        fov = 2.f * 180.f / M_PI * atan((right / near_clipping_plain));
        compute_projection_matrix(film_aspect_ratio);
#ifdef ALPHA_DEBUG
        print_info();
#endif
    }

    void print_info() {
        std::cout << "Field of view : " << fov << std::endl;
        std::cout << "Screen co-ords : " << top << "x" << right << std::endl;
        std::cout << "Img_dims" << img_width << "x" << img_height << std::endl;
        std::cout << "Matrix : " << std::endl;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                std::cout << world_to_cam[i][j] << "  ";
            }
            std::cout << std::endl;
        }
    }

    void compute_projection_matrix(float aspect) {
        float far = far_clipping_plain;
        float near = near_clipping_plain;
        if (fov <= 0 || aspect == 0) {
            assert(fov > 0 && aspect != 0);
            return;
        }

        float frustum_depth = far - near;
        float inv_depth = 1.f / frustum_depth;

        M_proj[1][1] = 1.f / tan(0.5f * fov);
        M_proj[0][0] = M_proj[1][1] / aspect;
        M_proj[2][2] = far * inv_depth;
        M_proj[3][2] = (-far * near) * inv_depth;
        M_proj[2][3] = -1.f;
        M_proj[3][3] = 0;
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
        // Convert to clip space
        math::Vec3f v_clip;
        M_proj.mult_vec_matrix(v_cam, v_clip);
        // Convert to raster space
        //
        raster.x = (v_clip.x + 1) / 2 * img_width;
        raster.y = (1 - v_clip.y) / 2 * img_height;
        raster.z = -v_cam.z;
    }

    void convert_to_raster(const math::Vec3f &v_world, math::Vec3f &raster) {
        math::Vec3f v_cam;
        convert_to_raster(v_world, raster, v_cam);
    }
};
}
#endif
