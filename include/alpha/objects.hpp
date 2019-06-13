//===---- objects ------ 3-D renderable object definitions ------*- C++ -*-===//
////
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Defines 3-D objects for ray tracing.
///
///
//===----------------------------------------------------------------------===//

#ifndef OBJECTS_ALPHA_HPP
#define OBJECTS_ALPHA_HPP

#include "math.hpp"

namespace alpha {
namespace object {

template <typename intersect_test>
struct Object {
    using RGB = alpha::buffers::RGB;
    RGB color;
    intersect_test tester;

    Object() : tester(intersect_test()) {}

    bool intersect(const Ray &cam_ray, float& t) { return tester(cam_ray, t); }
};

struct Circle {
    using Vec2f = alpha::math::Vec2f;

    Vec2f center;
    float radius;

    Circle() : center(0.f, 0.f), radius(1.f) {}
    Circle(Vec2f c, float r) : center(c), radius(r) {}

    bool operator()(const Ray &cam_ray, float& t) {
        // Ray-circle intersection.
        float dx = cam_ray.dir.x - center.x;
        float dy = cam_ray.dir.y - center.y;
        float check = dx * dx + dy * dy - radius * radius;
        t = 10;
        return check < 0.f;
    }
};

};
}

#endif
