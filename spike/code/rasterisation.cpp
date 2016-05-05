// Implement the simplest form of the rasterisation algorithm
#include "cow.hpp"
#include <camera_alpha.hpp>
#include <chrono>
#include <math_alpha.hpp>
#include <memory>
#include <rasteriser_alpha.hpp>
const int width = 640, height = 480, z_near = 1, z_far = 1000,
          focal_length = 20;
const float aperture_width = 0.980, aperture_height = 0.735;
auto cam_inst = std::make_shared<alpha::Camera>(
    width, height, 0.980, 0.735, 1, 1000, 20,
    std::initializer_list<std::initializer_list<float>>{
        {0.707107, -0.331295, 0.624695, 0},
        {0, 0.883452, 0.468521, 0},
        {-0.707107, -0.331295, 0.624695, 0},
        {-1.63871, -5.747777, -40.400412, 1},
    });
alpha::Rasteriser rast(cam_inst, 255);
// Render the cow for me
const int num_tris = 3156;
int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_tris; i++) {
        const alpha::Vec3f &v0 = vertices[nvertices[i * 3]];
        const alpha::Vec3f &v1 = vertices[nvertices[i * 3 + 1]];
        const alpha::Vec3f &v2 = vertices[nvertices[i * 3 + 2]];
        alpha::math::Vec2f st0 = st[stindices[i * 3]];
        alpha::math::Vec2f st1 = st[stindices[i * 3 + 1]];
        alpha::math::Vec2f st2 = st[stindices[i * 3 + 2]];
        rast.draw_triangle(v0, v1, v2, st0, st1, st2);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Total wall time : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1)
                     .count()
              << "ms\n";
    rast.dump_as_ppm("test.ppm");
    // const int width = 1366, height = 768;
    // auto cam_inst = std::make_shared<alpha::Camera>(
    // width, height, 0.980, 0.735, 1, 1000, 20, alpha::Matrix44f());
    // alpha::math::Vec2f st0 = {1, 1};
    // alpha::math::Vec2f st1 = {1, 1};
    // alpha::math::Vec2f st2 = {1, 1};
    // alpha::Rasteriser rast(cam_inst, 255);
    // alpha::Vec3f v0 = {0, 0, 1};
    // alpha::Vec3f v1 = {0.1, 0.1, 1};
    // alpha::Vec3f v2 = {0.1, 0, 1};
    // rast.draw_triangle(v0, v2, v1, st0, st1, st2);
    // rast.dump_as_ppm("test.ppm");
}
