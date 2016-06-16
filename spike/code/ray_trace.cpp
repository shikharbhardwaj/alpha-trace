#include <buffers_alpha.hpp>
#include <iostream>
#include <math_alpha.hpp>
#include <vector>
struct Ray {
    alpha::math::Vec3f dir;
};
struct Circle {
    float x, y, radius;
    bool operator()(const Ray &cam_ray) {
        if (cam_ray.dir.z > 0) {
            return true;
        }
        return false;
    }
};
template <typename intsersect_test> struct Object {
    using RGB = alpha::math::Vec3f;
    RGB color;
    intsersect_test tester;
    bool intsersect(const Ray &cam_ray) { return tester(cam_ray); }
};
Ray build_camera_ray(uint32_t x, uint32_t y);
std::vector<Object<Circle>> scene;
int main() {
    alpha::math::Vec3f background_color(0, 0, 0);
    const int img_width = 512, img_height = 512;
    Imagebuffer frame(img_width, img_height, 255);
    for (int j = 0; j < img_height; j++) {
        for (int i = 0; i < img_width; i++) {
            auto ray = build_camera_ray(i, j);
            for (auto &object : scene) {
                if (object.intsersect(ray) == true) {
                    frame.set(i, j, object.color.x, object.color.y,
                              object.color.z);
                } else {
                    frame.set(i, j, background_color.x, background_color.y,
                              background_color.z);
                }
            }
        }
    }
}
