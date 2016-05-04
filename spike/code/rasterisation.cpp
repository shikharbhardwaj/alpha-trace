// Implement the simplest form of the rasterisation algorithm
#include <camera_alpha.hpp>
#include <memory>
#include <rasteriser_alpha.hpp>
int main() {
    const int width = 1366, height = 768;
    auto cam_inst = std::make_shared<alpha::Camera>(
        width, height, 0.980, 0.735, 1, 1000, 20,
        std::initializer_list<std::initializer_list<float>>{
            {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}});
    alpha::Rasteriser rast(cam_inst, 255);
    alpha::math::Vec3f v0 = {0, 0, 2};
    alpha::math::Vec3f v1 = {0.5, 0.5, 5};
    alpha::math::Vec3f v2 = {0, 0.5, 3};
    rast.draw_triangle(v0, v1, v2);
    rast.dump_as_ppm("test.ppm");
}
