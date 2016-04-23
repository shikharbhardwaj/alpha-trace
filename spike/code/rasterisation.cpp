// Implement the simplest form of the rasterisation algorithm
#include <rasteriser_alpha.hpp>
int main() {
    const int width = 1366, height = 768;
    alpha::Vec2i v0 = {0, 0};
    alpha::Vec2i v1 = {width, 0};
    alpha::Vec2i v2 = {width, height};
    alpha::Rasteriser rast(width, height);
    rast.draw_triangle(v0, v1, v2);
    rast.dump_as_ppm("rast2d.ppm");
}
