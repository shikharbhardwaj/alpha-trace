#include <math_alpha.hpp>
#include <colours.hpp>
#include <iostream>
#include <random>
#include <limits>
// Tests for the math library
std::random_device rd;
std::mt19937 gen(rd());
void ok() { std::cout << colours::green << "OK ✓ " << colours::reset; }
void nok() { std::cout << colours::red << "ERROR ❌ " << colours::reset; }
template <typename T> void expected(T a, T b) {
    if (fabs(fabs(a) - fabs(b)) <= std::numeric_limits<T>::epsilon()) {
        ok();
    } else {
        nok();
        std::cout << " Expected : " << a << ", got : " << b << " ";
    }
}
int main() {
    std::uniform_real_distribution<float> dist(-500, 500);
    std::cout << "Testing math library : ";
    alpha::vec3<float> test_vec(dist(gen), dist(gen), dist(gen));
    std::cout << "\n\t\tTesting " << colours::cyan << "alpha::vec3"
              << colours::reset;
    std::cout << "\nalpha::vec3::mod \t:\t";
    float x, y, z;
    x = test_vec[0];
    y = test_vec[1];
    z = test_vec[2];
    expected(test_vec.mod(), float(sqrt(x * x + y * y + z * z)));
    float multiplier = dist(gen);
    std::cout << "\nalpha::vec3::operator* \t:\t";
    test_vec = test_vec * multiplier;
    x *= multiplier;
    y *= multiplier;
    z *= multiplier;
    expected(test_vec[0], x);
    expected(test_vec[1], y);
    expected(test_vec[2], z);
    std::cout << "\nalpha::vec3::normalize \t:\t";
    float inv_mag = 1.0 / test_vec.mod();
    test_vec.normalize();
    x *= inv_mag;
    y *= inv_mag;
    z *= inv_mag;
    expected(test_vec[0], x);
    expected(test_vec[1], y);
    expected(test_vec[2], z);
    std::cout << "\nalpha::vec3::dot \t:\t";
    alpha::vec3<float> ultimate(dist(gen), dist(gen), dist(gen));
    x *= ultimate[0];
    y *= ultimate[1];
    z *= ultimate[2];
    expected(test_vec.dot(ultimate), x + y + z);
    test_vec = alpha::vec3<float>(x, y, z);
    std::cout << "\nalpha::vec3::operator+ \t:\t";
    test_vec = test_vec + ultimate;
    x += ultimate[0];
    y += ultimate[1];
    z += ultimate[2];
    expected(test_vec[0], x);
    expected(test_vec[1], y);
    expected(test_vec[2], z);
    std::cout << "\nalpha::vec3::operator- \t:\t";
    ultimate = alpha::vec3<float>(dist(gen), dist(gen), dist(gen));
    test_vec = test_vec - ultimate;
    x -= ultimate[0];
    y -= ultimate[1];
    z -= ultimate[2];
    expected(test_vec[0], x);
    expected(test_vec[1], y);
    expected(test_vec[2], z);
    std::cout << "\nalpha::vec3::cross \t:\t";
    float xx, yy, zz;
    xx = y * ultimate[2] - z * ultimate[1];
    yy = x * ultimate[2] - z * ultimate[0];
    zz = x * ultimate[1] - y * ultimate[0];
    test_vec = test_vec.cross(ultimate);
    expected(test_vec[0], xx);
    expected(test_vec[1], yy);
    expected(test_vec[2], zz);
    std::cout << std::endl;
}
