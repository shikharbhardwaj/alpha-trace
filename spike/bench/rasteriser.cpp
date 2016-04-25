// A simple benchmark to test rasteriser performance
#define NONIUS_RUNNER
#include <nonius.h++>
#include <rasteriser_alpha.hpp>
const int width = 512, height = 512;
alpha::Vec2i v2 = {width + 3, 0};
alpha::Vec2i v1 = {0, 0};
alpha::Vec2i v0 = {width, height};
alpha::Rasteriser rast(width, height);
NONIUS_BENCHMARK("Rasteriser", [](nonius::chronometer meter) {
    meter.measure([] { rast.draw_triangle(v0, v1, v2); });
});
// Curren time : 6.8ms
