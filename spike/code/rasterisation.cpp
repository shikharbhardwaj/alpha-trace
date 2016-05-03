// Implement the simplest form of the rasterisation algorithm
#include <camera_alpha.hpp>
#include <rasteriser_alpha.hpp>
int main() {
    const int width = 1366, height = 768;
    alpha::Camera cam(width, height, 0.980, 0.735, 1, 1000, 20,
                      {{0.707107, -0.331295, 0.624695, 0},
                       {0, 0.883452, 0.468521, 0, -0.707107},
                       {-0.331295, 0.624695, 0, -1.63871},
                       {-5.747777, -40.400412, 1}});
    alpha::Rasteriser rast(std::shared_ptr<alpha::Camera>(&cam), 255);
}
