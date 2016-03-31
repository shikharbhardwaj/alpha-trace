#include <math_alpha.hpp>
#include <colours.hpp>
#include <iostream>
#include <random>
#include <chrono>
#include <limits>
// Tests for the math library
bool fail = false;
std::random_device rd;
std::mt19937 gen(rd());
void ok() { std::cout << colours::green << "OK ✓ " << colours::reset; }
void nok() { std::cout << colours::red << "ERROR ❌ " << colours::reset; }
template <typename T> void expected(T a, T b) {
    if (alpha::is_equal(a, b)) {
        ok();
    } else {
        nok();
        fail = true;
        std::cout << "\n\tExpected : " << a << ", got : " << b << " ";
        std::cout << "Δ = " << a - b;
    }
}
int main() {
    std::uniform_real_distribution<float> dist(-500, 500);
    std::cout << "Testing math library : ";
    alpha::vec3<float> test_vec(dist(gen), dist(gen), dist(gen));
    std::cout << "\n\t\tTesting " << colours::cyan << "alpha::vec3"
              << colours::reset;
    std::cout << "\nalpha::vec3::mod \t\t:\t";
    float x, y, z;
    x = test_vec[0];
    y = test_vec[1];
    z = test_vec[2];
    expected(test_vec.mod(), float(sqrt(x * x + y * y + z * z)));
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
    float inv_mag = 1.0 / test_vec.mod();
    test_vec.normalize();
    x *= inv_mag;
    y *= inv_mag;
    z *= inv_mag;
    expected(test_vec[0], x);
    expected(test_vec[1], y);
    expected(test_vec[2], z);
    std::cout << "\nalpha::vec3::dot \t\t:\t";
    alpha::vec3<float> ultimate(dist(gen), dist(gen), dist(gen));
    x *= ultimate[0];
    y *= ultimate[1];
    z *= ultimate[2];
    expected(test_vec.dot(ultimate), x + y + z);
    test_vec = alpha::vec3<float>(x, y, z);
    std::cout << "\nalpha::vec3::operator+ \t\t:\t";
    test_vec = test_vec + ultimate;
    x += ultimate[0];
    y += ultimate[1];
    z += ultimate[2];
    expected(test_vec[0], x);
    expected(test_vec[1], y);
    expected(test_vec[2], z);
    std::cout << "\nalpha::vec3::operator- \t\t:\t";
    ultimate = alpha::vec3<float>(dist(gen), dist(gen), dist(gen));
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
    test_vec = test_vec.cross(ultimate);
    expected(test_vec[0], xx);
    expected(test_vec[1], yy);
    expected(test_vec[2], zz);
    std::cout << "\n\t\tTesting " << colours::cyan << "alpha::mat44"
              << colours::reset;
    alpha::mat44<float> test_mat{{dist(gen), dist(gen), dist(gen), dist(gen)},
                                 {dist(gen), dist(gen), dist(gen), dist(gen)},
                                 {dist(gen), dist(gen), dist(gen), dist(gen)},
                                 {dist(gen), dist(gen), dist(gen), dist(gen)}};
    alpha::mat44<float> test_mat2 = test_mat;
    test_mat = test_mat.transpose();
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
    std::cout << "\nalpha::mat44_det\t\t:\t";
    alpha::mat44<float> sample{
        {3, -2, 1, 2}, {2, 3, -2, 4}, {3, 2, 3, 4}, {-2, 4, 0, 5}};
    expected(alpha::mat44_det(sample), float(286));
    std::cout << "\nalpha::gauss_elimination\t:\t";
    alpha::mat44<float> sample2{
        {1, 1, 1, 6}, {1, -1, 2, 5}, {3, 1, 1, 8}, {2, -2, 3, 7}};
    if (alpha::gauss_elimination(sample2) ==
        alpha::mat44<float>{{3, 1, 1, 8},
                            {0, -8.f / 3.f, 7.f / 3.f, 5.f / 3.f},
                            {0, 0, 1.25f, 3.75f},
                            {0, 0, 0, 0}}) {
        expected(0, 0);
    } else {
        expected(1, 0);
    }
    if (!fail) {
        std::cout << "\n\n" << colours::green << "[OK] " << colours::reset
                  << "All tests successful";
    } else {
        std::cout << "\n\n" << colours::red << "[ERROR] " << colours::reset
                  << "Some tests failed";
    }
    std::cout << std::endl;
}
