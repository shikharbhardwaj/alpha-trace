// Tests for the math library
#include <chrono>
#include <colours.hpp>
#include <iostream>
#include <limits>
#include <math_alpha.hpp>
#include <random>
bool fail = false;
std::random_device rd;
std::mt19937 gen(rd());
void ok() { std::cout << colours::green << "OK ✓ " << colours::reset; }
void nok() { std::cout << colours::red << "ERROR ❌ " << colours::reset; }
void expected(float a, float b) {
    if (alpha::math::is_equal(a, b)) {
        ok();
    } else {
        nok();
        fail = true;
        std::cout << "\n\tExpected : " << a << ", got : " << b << " ";
        std::cout << "Δ = " << a - b;
    }
}
int main() {
    using namespace alpha::math;
    std::uniform_real_distribution<float> dist(-500000, 500000);
    std::cout << "Testing math library : ";
    Vec3<float> test_vec(dist(gen), dist(gen), dist(gen));
    std::cout << "\n\t\tTesting " << colours::cyan << "alpha::vec3"
              << colours::reset;
    std::cout << "\nalpha::vec3::mod \t\t:\t";
    float x, y, z;
    x = test_vec[0];
    y = test_vec[1];
    z = test_vec[2];
    expected(test_vec.length(), float(sqrt(x * x + y * y + z * z)));
    float multiplier = dist(gen);
    std::cout << "\nalpha::vec3::operator* \t\t:\t";
    test_vec = test_vec * multiplier;
    x *= multiplier;
    y *= multiplier;
    z *= multiplier;
    expected(test_vec[0], x);
    expected(test_vec[1], y);
    expected(test_vec[2], z);
    std::cout << "\nalpha::vec3::normalize \t\t:\t";
    float inv_mag = 1.0 / test_vec.length();
    test_vec.normalize();
    x *= inv_mag;
    y *= inv_mag;
    z *= inv_mag;
    expected(test_vec[0], x);
    expected(test_vec[1], y);
    expected(test_vec[2], z);
    std::cout << "\nalpha::vec3::dot \t\t:\t";
    Vec3<float> ultimate(dist(gen), dist(gen), dist(gen));
    x *= ultimate[0];
    y *= ultimate[1];
    z *= ultimate[2];
    expected(test_vec.dot_product(ultimate), (x + y) + z);
    test_vec = Vec3<float>(x, y, z);
    std::cout << "\nalpha::vec3::operator+ \t\t:\t";
    test_vec = test_vec + ultimate;
    x += ultimate[0];
    y += ultimate[1];
    z += ultimate[2];
    expected(test_vec[0], x);
    expected(test_vec[1], y);
    expected(test_vec[2], z);
    std::cout << "\nalpha::vec3::operator- \t\t:\t";
    ultimate = Vec3<float>(dist(gen), dist(gen), dist(gen));
    test_vec = test_vec - ultimate;
    x -= ultimate[0];
    y -= ultimate[1];
    z -= ultimate[2];
    expected(test_vec[0], x);
    expected(test_vec[1], y);
    expected(test_vec[2], z);
    std::cout << "\nalpha::vec3::cross \t\t:\t";
    float xx, yy, zz;
    xx = y * ultimate[2] - z * ultimate[1];
    yy = x * ultimate[2] - z * ultimate[0];
    zz = x * ultimate[1] - y * ultimate[0];
    test_vec = test_vec.cross_product(ultimate);
    expected(test_vec[0], xx);
    expected(test_vec[1], yy);
    expected(test_vec[2], zz);
    std::cout << "\n\t\tTesting " << colours::cyan << "alpha::mat44"
              << colours::reset;
    Matrix44<float> test_mat{{dist(gen), dist(gen), dist(gen), dist(gen)},
                             {dist(gen), dist(gen), dist(gen), dist(gen)},
                             {dist(gen), dist(gen), dist(gen), dist(gen)},
                             {dist(gen), dist(gen), dist(gen), dist(gen)}};
    Matrix44<float> test_mat2 = test_mat;
    test_mat.transpose();
    bool found = true;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (test_mat2[j][i] != test_mat[i][j]) {
                found = false;
                break;
            }
        }
    }
    std::cout << "\nalpha::mat44::transpose\t\t:\t";
    if (!found) {
        expected(1, 0);
    } else {
        expected(0, 0);
    }
    std::cout << "\nalpha::mat44::inverse\t\t:\t";
    Matrix44<float> inv_test{
        {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 3, 4}, {0, 0, 1, 1}};
    Matrix44<float> inv_pre{
        {1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, -1, 4}, {0, 0, 1, -3}};
    inv_test.invert();
    if (inv_test == inv_pre) {
        expected(0, 0);
    } else {
        expected(1, 0);
    }
    std::cout << "\nalpha::mat44::opertor==\t\t:\t";
    expected(1, 1);
    if (!fail) {
        std::cout << "\n\n"
                  << colours::green << "[OK] " << colours::reset
                  << "All tests successful";
    } else {
        std::cout << "\n\n"
                  << colours::red << "[ERROR] " << colours::reset
                  << "Some tests failed";
    }
    std::cout << std::endl;
}
