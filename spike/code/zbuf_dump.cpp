// Implement the simplest form of the rasterisation algorithm
#include "shader.hpp"
#include <chrono>
#include <memory>

#include <alpha/math.hpp>
#include <alpha/camera.hpp>
#include <alpha/rasteriser.hpp>

int render_triangle::id = 0;
const int width = 640, height = 480;
const float aperture_width = 0.980f, aperture_height = 0.735f,
	z_near = 1.f, z_far = 1000.f, focal_length = 20.f;
alpha::math::Matrix44f world2cam({
        0.707107f, -0.331295f, 0.624695f, 0.f,
        0.f, 0.883452f, 0.468521f, 0.f,
        -0.707107f, -0.331295f, 0.624695f, 0.f,
        -1.63871f, -5.747777f, -40.400412f, 1.f,
});
auto cam_inst = std::make_shared<alpha::Camera>(
    width, height, aperture_width, aperture_height, z_near,
	z_far, focal_length, world2cam);
render_triangle renderer;
alpha::Rasteriser<render_triangle> rast(cam_inst, renderer);
// Render the cow for me
const int num_tris = 3156;
int main() {
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < num_tris; i++) {
        const alpha::math::Vec3f &v0 = vertices[nvertices[i * 3]];
        const alpha::math::Vec3f &v1 = vertices[nvertices[i * 3 + 1]];
        const alpha::math::Vec3f &v2 = vertices[nvertices[i * 3 + 2]];
        rast.draw_triangle(v0, v1, v2);
        renderer.id++;
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Total wall time : "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1)
                     .count()
              << "ms\n";
    rast.dump_as_ppm("test_noAA.ppm");
    rast.dump_zbuf("zbuf.ppm");
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
