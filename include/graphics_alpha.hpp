//===--- graphics.hpp --- Math abstraction definitions ----------*- C++ -*-===//
////
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
///  Consists of abstractions over graphics
///
///
//===----------------------------------------------------------------------===//
#ifndef GRAPHICS_ALPHA_HPP
#define GRAPHICS_ALPHA_HPP
#include <math_alpha.hpp>
#include <iostream>
namespace alpha {
void compute_pixel_coords(const Vec3f &p_world, const Matrix44f &world_to_cam,
                          const float canvas_width, const float canvas_height,
                          const uint32_t img_width, const uint32_t img_height,
                          Vec2i &p_raster) {
    // Transform the given point in world space to camera space
    // No bounds checking
    Vec3f p_cam;
    Vec2f p_NDC, p_screen;
    world_to_cam.mult_vec_matrix(p_world, p_cam);
    // The co-ordinates of the point wrt the camera in screen space, using
    // perspective projection
    p_screen.x = -p_cam.x / p_cam.z;
    p_screen.y = -p_cam.y / p_cam.z;
    // Convert to NDC and rasterize to the screen
    p_NDC.x = (p_screen.x + canvas_width * 0.5) / canvas_width;
    p_NDC.y = (p_screen.y + canvas_height * 0.5) / canvas_height;
    // NDC to raster
    p_raster.x = std::floor(p_NDC.x * img_width);
    p_raster.y = std::floor((1 - p_NDC.y) * img_height);
}
bool compute_pixel_coords(const Vec3f &p_world, const Matrix44f &world_to_cam,
                          const float b, const float l, const float t,
                          const float r, const float near,
                          const uint32_t img_width, const uint32_t img_height,
                          Vec2i &p_raster) {
    Vec3f p_cam;
    Vec2f p_NDC, p_screen;
    world_to_cam.mult_vec_matrix(p_world, p_cam);
    // Perform perspective divide
    p_screen.x = -p_cam.x / p_cam.z * near;
    p_screen.y = -p_cam.y / p_cam.z * near;
    // Convert to NDC
    p_NDC.x = (p_screen.x + r) / (2 * r);
    p_NDC.y = (p_screen.y + t) / (2 * t);
    // Convert to raster
    p_raster.x = p_NDC.x * img_width;
    p_raster.y = (1 - p_NDC.y) * img_height;
    bool visible = true;
    // Check if visible
    if (p_screen.x > r || p_screen.y > t || p_screen.x < l || p_screen.y < b) {
        visible = false;
    }
    return visible;
}
}
#endif
