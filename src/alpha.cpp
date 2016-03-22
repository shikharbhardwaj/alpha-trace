#include <iostream>
#include <math_alpha.hpp>
int main() {
    alpha::vec3<float> v(1, 2, 3);
    alpha::mat44<int> mat;
    mat.dump();
    alpha::mat44<int> ma2{
        {1, 0, 0, 0}, {0, 2, 0, 0}, {4, 5, 6, 7}, {7, 8, 9, 0}};
    ma2.dump();
    std::cout << "\n";
}
