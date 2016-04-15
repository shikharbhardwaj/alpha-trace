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
namespace alpha {
bool compute_pixel_coords(const Vec3f &p_world, const Matrix44f &world_to_cam,
                          const float canvas_width, const float canvas_height,
                          const int img_width, const int img_height,
                          Vec2i &p_raster) {
    // Transform the given point in world space to camera space
    Vec3f p_cam;
    world_to_cam.mult_vec_matrix(p_world, p_cam);
    Vec2f p_screen;
    // The co-ordinates of the point wrt the camera in screen space, using
    // perspective projection
    p_screen.x = -p_cam.x / p_cam.z;
    p_screen.y = -p_cam.y / p_cam.z;
    // Check is the point is visible in the canvas space
    if (std::abs(p_screen.x) > canvas_width ||
        std::abs(p_screen.y) > canvas_height) {
        return false;
    }
    // Convert to NDC and rasterize to the screen
    Vec2f p_NDC;
    p_NDC.x = (p_screen.x + canvas_width / 2) / canvas_width;
    p_NDC.y = (p_screen.y + canvas_height / 2) / canvas_height;
    // NDC to raster
    p_raster.x = std::floor(p_NDC.x * img_width);
    p_raster.y = std::floor((1 - p_NDC.y) * img_height);
    return true;
}
}
#endif
