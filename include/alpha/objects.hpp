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
namespace objects {

struct Object {
    using RGB = alpha::buffers::RGB;
    RGB color;

    Object() {}

	virtual bool intersect(const Ray&, float&) { return false;  }
};


struct Circle : public Object {
    using Vec2f = alpha::math::Vec2f;

    Vec2f center;
    float radius;

    Circle() : center(0.f, 0.f), radius(1.f) {}
	Circle(float cx, float cy, float r) : center(cx, cy), radius(r) {}
    Circle(Vec2f c, float r) : center(c), radius(r) {}

    bool intersect(const Ray &cam_ray, float& t) {
        // Ray-circle intersection.
        float dx = cam_ray.dir.x - center.x;
        float dy = cam_ray.dir.y - center.y;
        float check = dx * dx + dy * dy - radius * radius;
        t = 10;
        return check < 0.f;
    }
};

struct Sphere : public Object {
	using Vec3f = alpha::math::Vec3f;

	Vec3f center;
	float radius;

	Sphere() : center(0.f, 0.f, 0.f), radius(1.f) {}
	Sphere(Vec3f c, float r) : center(c), radius(r) {}

	bool operator() (const Ray& cam_ray, float& t) {
		const auto& o = cam_ray.origin;
		const auto& d = cam_ray.dir;

		auto p = o - center;

		float a = d.norm();
		float b = 2 * p.dot_product(d);
		float c = p.norm() - radius * radius;

		// Solve quadratic equation.
		float D = b * b - 4 * a * c;

		if (D < 0.f) return false;

		t = (-b + sqrt(D)) / (2.f * a);
		return true;
	}
};

};
}

#endif
