// A simple benchmark to test rasteriser performance
#define NONIUS_RUNNER
#include "shader.hpp"
#include <nonius.h++>
#include <rasteriser_alpha.hpp>
int render_triangle::id = 0; // The triangle to start from
const int width = 640, height = 480;
auto cam_inst = std::make_shared<alpha::Camera>(
    width, height, 0.980, 0.735, 1, 1000, 20,
    std::initializer_list<std::initializer_list<float>>{
        {0.707107, -0.331295, 0.624695, 0},
        {0, 0.883452, 0.468521, 0},
        {-0.707107, -0.331295, 0.624695, 0},
        {-1.63871, -5.747777, -40.400412, 1},
    });
render_triangle renderer;
alpha::Rasteriser<render_triangle> rast(cam_inst, renderer, 255);
// Render the cow for me
const int num_tris = 3156;
NONIUS_BENCHMARK("Rasteriser", [](nonius::chronometer meter) {
    meter.measure([] {
        for (volatile int i = 0; i < num_tris; i++) {
            const alpha::math::Vec3f &v0 = vertices[nvertices[i * 3]];
            const alpha::math::Vec3f &v1 = vertices[nvertices[i * 3 + 1]];
            const alpha::math::Vec3f &v2 = vertices[nvertices[i * 3 + 2]];
            rast.draw_triangle(v0, v1, v2);
            renderer.id++;
        }
    });

});
