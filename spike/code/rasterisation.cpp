// Implement the simplest form of the rasterisation algorithm
#include "shader.hpp"
#include <chrono>
#include <memory>

#include <alpha/math.hpp>
#include <alpha/camera.hpp>
#include <alpha/rasteriser.hpp>

int render_triangle::id = 0;
const int width = 4 * 640, height = 4 * 480;
const float z_near = 1.f, z_far = 1000.f, focal_length = 20.f;
const float aperture_width = 0.980f, aperture_height = 0.735f;
alpha::math::Matrix44f world2cam(
    {0.707107f, -0.331295f, 0.624695f, 0.f,
    -0.707107f, -0.331295f, 0.624695f, 0.f,
    -1.63871f, -5.747777f, -40.400412f, 1.f,
    0.f, 0.f, 0.f, 1.f});

auto cam_inst = std::make_shared<alpha::Camera>(
    width, height, aperture_width, aperture_height, z_near, z_far, focal_length,
    world2cam);
render_triangle renderer;
alpha::Rasteriser<render_triangle> rast(cam_inst);
// Render the cow for me
const int num_tris = 3156;
int main() {
    using namespace std::chrono;
    auto t1 = high_resolution_clock::now();
    for (int i = 0; i < num_tris; i++) {
        const alpha::math::Vec3f &v0 = vertices[nvertices[i * 3]];
        const alpha::math::Vec3f &v1 = vertices[nvertices[i * 3 + 1]];
        const alpha::math::Vec3f &v2 = vertices[nvertices[i * 3 + 2]];
        rast.draw_triangle(v0, v1, v2);
        renderer.id++;
    }
    auto t2 = high_resolution_clock::now();
    std::cout << "Total wall time : "
              << duration_cast<milliseconds>(t2 - t1).count() << "ms\n";
    rast.dump_as_ppm("test.ppm");
}
