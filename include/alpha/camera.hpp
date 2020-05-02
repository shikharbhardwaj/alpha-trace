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

#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/fmt/ostr.h>

#include "math.hpp"

namespace alpha {
enum class fit_resolution_gate {
    Fill = 0, Overscan
};

class Camera {
	using Ray = math::Ray;
	using Vec3f = math::Vec3f;
	using Matrix44f = math::Matrix44f;

private:
    float inch_to_mm = 25.4f;
    float film_aperture_width, film_aperture_height;
    fit_resolution_gate fit_setting;
    float near_clipping_plain, far_clipping_plain;
    float focal_length;
    float top, bottom, left, right, fov;
    math::Matrix44f M_proj;
    math::Matrix44f world_to_cam;
    math::Matrix44f cam_to_world;
    math::Vec3f origin;

public:
    uint32_t img_width, img_height;

    Camera() = delete;

    Camera(const std::string &file_name, bool column_major = false) {
        // Import settings from a file
        spdlog::info("Initializing camera settings from settings file: {}",
                file_name);
        std::ifstream handle(file_name);
        handle >> img_width >> img_height >> film_aperture_width >>
               film_aperture_height >> near_clipping_plain >> far_clipping_plain >>
               focal_length;
        math::Matrix44f w2cam;
        if (column_major) {
            for (uint8_t i = 0; i < 4; i++) {
                for (uint8_t j = 0; j < 4; j++) {
                    handle >> w2cam[j][i];
                }
            }
        } else {
            for (uint8_t i = 0; i < 4; i++) {
                for (uint8_t j = 0; j < 4; j++) {
                    handle >> w2cam[i][j];
                }
            }
        }
        set_world_to_cam(w2cam);
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
              focal_length(f_length), img_width(width),
              img_height(height) {
        fit_setting = setting;
        set_world_to_cam(w2cam);
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

        fov = static_cast<float>(2.f * 180.f / M_PI * atan((right / near_clipping_plain)));

        compute_projection_matrix(film_aspect_ratio);

        spdlog::info("Field of view: {}", fov);
        spdlog::info("Screen co-ords: {}, {}", top, right);
        spdlog::info("Image dimensions: {}, {}", img_width, img_height);
        spdlog::info("World_to_cam matrix:");
        spdlog::info("{}", world_to_cam);
        spdlog::info("{}", M_proj);
    }

    void compute_projection_matrix(float aspect) {
        float far = far_clipping_plain;
        float near = near_clipping_plain;

        assert(fov > 0 && aspect != 0);

        float frustum_depth = far - near;
        float inv_depth = 1.f / frustum_depth;
		M_proj.eye();
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

    math::Matrix44f get_world_to_cam() {
        return world_to_cam;
    }

    void set_world_to_cam(const math::Matrix44f& w2cam) {
        world_to_cam = w2cam;
        cam_to_world = w2cam.inverse();
        cam_to_world.mult_dir_matrix(math::Vec3f(0), origin);
    }

	void set_cam_to_world(const math::Matrix44f& cam2world) {
		cam_to_world = cam2world;
		world_to_cam = cam2world.inverse();
		cam_to_world.mult_dir_matrix(math::Vec3f(0), origin);
	}

    Ray get_camera_ray(uint32_t i, uint32_t j) {
        assert(i < img_width);
        assert(j < img_height);

        float aspect = img_width / (float)img_height;
        float scale = (float)tan(fov * M_PI / 360.f);

        float x = (2 * ((i + 0.5f) / img_width) - 1) * scale * aspect;
        float y = (1 - 2 * ((j + 0.5f) / img_height)) * scale;

        math::Vec3f dir;
        cam_to_world.mult_dir_matrix(math::Vec3f(x, y, -1), dir);

        dir.normalize();
        return Ray(origin, dir);
    }

	void look_at(const Vec3f& from, const Vec3f& to) {
		Vec3f forward = (from - to).normalize();
		Vec3f temp = { 0.f, 1.f, 0.f };
		temp.normalize();
		Vec3f rt = temp.cross_product(forward).normalize();

		Vec3f up = forward.cross_product(rt).normalize();

		Matrix44f cam2world;

		cam2world[0][0] = rt.x;
		cam2world[0][1] = rt.y;
		cam2world[0][2] = rt.z;
		cam2world[0][3] = 0.f;

		cam2world[1][0] = up.x;
		cam2world[1][1] = up.y;
		cam2world[1][2] = up.z;
		cam2world[1][3] = 0.f;

		cam2world[2][0] = forward.x;
		cam2world[2][1] = forward.y;
		cam2world[2][2] = forward.z;
		cam2world[2][3] = 0.f;

		cam2world[3][0] = from.x;
		cam2world[3][1] = from.y;
		cam2world[3][2] = from.z;
		cam2world[3][3] = 1.f;

		set_cam_to_world(cam2world);
	}
}; // namespace camera
} // namespace alpha

#endif
