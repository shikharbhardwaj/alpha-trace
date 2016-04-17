// POC to find the canvas coords
#include <iostream>
#include <cmath>
#include <math_alpha.hpp>
#include <prettyprint.hpp>
float focal_length = 35;            // mm
float film_aperture_width = 0.980;  // in
float film_aperture_height = 0.735; // in
static const float inch_to_mm = 25.4;
float near_clipping_plain = 0.1;
float far_clipping_plain = 1000;
int main() {
    float film_aspect_ratio = film_aperture_width / film_aperture_height;
    float top = ((film_aperture_height * inch_to_mm / 2) / focal_length) *
                near_clipping_plain;
    float right = top * film_aspect_ratio;
    float left = -right;
    float bottom = -top;
    std::cout << "Co-ordinates of the canvas : ";
    auto first = std::make_pair(right, top);
    auto second = std::make_pair(left, top);
    auto third = std::make_pair(left, bottom);
    auto fourth = std::make_pair(right, bottom);
    std::cout << "\nFirst : " << first;
    std::cout << "\nSecond : " << second;
    std::cout << "\nThird : " << third;
    std::cout << "\nFourth : " << fourth;
}
