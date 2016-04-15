#include <math_alpha.hpp>
#include <ppm_alpha.hpp>
#include <cmath>
int main() {
    std::cout << "Want to print a sphere in the centre of the image space";
    alpha::ppm_image img("sphere.ppm", 512, 512);
    alpha::Vec3i white(255, 255, 255);
    // The equation of the sphere is x^2 + y^2 = 1
    double sp_h = 128.f, sp_w = 128.f;
    for (double i = 0.001; i < 1; i += 0.00001) {
        double y_dim = sqrt(1 - i * i);
        img.set(round((1.f + i) * sp_w), round((1.f + y_dim) * sp_h), white);
        img.set(round((1.f - i) * sp_w), round((1.f - y_dim) * sp_h), white);
        img.set(round((1.f + i) * sp_w), round((1.f - y_dim) * sp_h), white);
        img.set(round((1.f - i) * sp_w), round((1.f + y_dim) * sp_h), white);
    }
    img.dump();
}
