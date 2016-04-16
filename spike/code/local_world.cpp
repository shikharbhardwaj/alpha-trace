#include <math_alpha.hpp>
#include <graphics_alpha.hpp>
#include <iostream>
int main() {
    alpha::Matrix44<float> m{{0.718762, 0.615033, -0.324214, 0},
                             {-0.393732, 0.7444416, 0.539277, 0},
                             {0.573024, -0.259959, 0.777216, 0},
                             {0.526967, 1.254234, -2.532150, 1}};
    m.invert();
    alpha::Vec3f Pworld(-0.315792, 1.4489, -2.48901);
    alpha::Vec2i Praster;
    alpha::compute_pixel_coords(Pworld, m.inverse(), 0.1, 0.1, 256, 256,
                                Praster);
    std::cerr << Praster << std::endl;
}
