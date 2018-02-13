// Implement the simplest form of the rasterisation algorithm
#include "shader.hpp"
#include <chrono>
#include <memory>

#include <alpha/rasteriser.hpp>
#include <alpha/camera.hpp>
#include <alpha/math.hpp>

using namespace alpha;

int render_triangle::id = 0;
const int width = 2 * 640, height = 2 * 480;

const float aperture_width = 0.980f, aperture_height = 0.735f, focal_length = 20, z_near = 1, z_far = 1000;
auto cam_inst = std::make_shared<alpha::Camera>(
    width, height, aperture_width, aperture_height, z_near, z_far, focal_length,
    std::initializer_list<std::initializer_list<float>>{
        {0.707107f, -0.331295f, 0.624695f, 0.f},
        {0.f, 0.883452f, 0.468521f, 0.f},
        {-0.707107f, -0.331295f, 0.624695f, 0.f},
        {-1.63871f, -5.747777f, -40.400412f, 1.f},
    });
render_triangle renderer;
alpha::Rasteriser<render_triangle> rast(cam_inst, renderer);
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
    std::cout << duration_cast<milliseconds>(t2 - t1).count() << "\n";
	  rast.dump_as_ppm("test.ppm");
}
