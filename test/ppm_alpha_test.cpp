#include <ppm_alpha.hpp>
int main() {
    // A sample test
    alpha::ppm_image first("my_img.ppm", 512, 512);
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 10; j++) {
            first.set(i + 256, 256 + j, alpha::Vec3<int>(255, 255, 255));
        }
    }
    first.dump();
}
