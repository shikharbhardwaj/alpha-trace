#include <iostream>
#include <vector>

#include <alpha/buffers.hpp>
#include <alpha/camera.hpp>
#include <alpha/math.hpp>
#include <alpha/objects.hpp>

using namespace alpha::buffers;
using namespace alpha::math;
using namespace alpha::object;
using namespace alpha;
using namespace std;

const int width = 1920, height = 1080;
const float aperture_width = 0.980f, aperture_height = 0.735f, focal_length = 20, z_near = 1, z_far = 1000;

//alpha::math::Matrix44f world2cam(
//    { 0.707107f, -0.331295f, 0.624695f, 0.f,
//            0.f,  0.883452f, 0.468521f, 0.f,
//     -0.707107f, -0.331295f, 0.624695f, 0.f,
//      -1.53871f, -5.747777f, -40.400412f, 1.f });

alpha::math::Matrix44f world2cam(
    { 1.0000f, 0.0000f, 0.0000f, 0.0000f,
    0.0000f, 1.0000f, 0.0000f, 0.0000f,
    0.0000f, 0.0000f, 1.0000f, 0.0000f,
    0.0000f, 0.0000f, 0.0000f, 1.0000f, }
);


Camera cam(width, height, aperture_width, aperture_height, z_near, z_far, focal_length,
        world2cam);

std::vector<Object<Circle>> scene;

int main() {
    Circle center_circle({0.f, 0.f}, 0.25);

    Object<Circle> obj;

    obj.tester = center_circle;
    obj.color = { 255, 0, 0 };
    scene.push_back(obj);

    alpha::buffers::RGB background_color(0, 0, 0);
    Imagebuffer frame(width, height, 255);

    for (int j = 0; j < height; j++) {
        for (int i = 0; i < width; i++) {
            auto ray = cam.get_camera_ray(i, j);
            for (auto &object : scene) {
                float t;

                // Check for intersection.
                if (object.intersect(ray, t) == true) {
                    frame.set(i, j, object.color.x, object.color.y,
                              object.color.z);
                } else {
                    frame.set(i, j, background_color.x, background_color.y,
                              background_color.z);
                }
            }
        }
    }
    frame.dump_as_ppm("trace.ppm");
}
