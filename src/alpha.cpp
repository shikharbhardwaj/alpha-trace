#include <iostream>
#include <math_alpha.hpp>
int main() {
    alpha::Vec3<float> v(1, 2, 3);
    alpha::Matrix44<int> mat;
    alpha::Matrix44<int> ma2{
        {1, 0, 0, 0}, {0, 2, 0, 0}, {4, 5, 6, 7}, {7, 8, 9, 0}};
    std::cout << "\nThis is an edit\n";
}
