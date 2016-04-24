// A simple benchmark to test rasteriser performance
#define NONIUS_RUNNER
#include <nonius.h++>
#include <rasteriser_alpha.hpp>
const int width = 1366, height = 768;
alpha::Vec2i v2 = {width, 0};
alpha::Vec2i v1 = {0, 0};
alpha::Vec2i v0 = {width, height};
alpha::Rasteriser rast(width, height);
NONIUS_BENCHMARK("Rasteriser", [](nonius::chronometer meter) {
    meter.measure([] { rast.draw_triangle(v0, v1, v2); });
});
