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
#include "buffers.hpp"

namespace alpha {
namespace objects {

struct Object {
    using RGB = buffers::RGB;
	using Ray = math::Ray;
	using Point = math::Vec3f;
	using Vec2f = math::Vec2f;

    RGB color;

    Object() {}

	virtual bool intersect(const Ray&, float&) const { return false;  }
	virtual void get_surface_data(const Point&, Point&, Vec2f&) const {}
};


struct Circle : public Object {
    using Vec2f = alpha::math::Vec2f;

    Vec2f center;
    float radius;

    Circle() : center(0.f, 0.f), radius(1.f) {}
	Circle(float cx, float cy, float r) : center(cx, cy), radius(r) {}
    Circle(Vec2f c, float r) : center(c), radius(r) {}

    bool intersect(const Ray &cam_ray, float& t) const {
        // Ray-circle intersection.
        float dx = cam_ray.dir.x - center.x;
        float dy = cam_ray.dir.y - center.y;
        float check = dx * dx + dy * dy - radius * radius;
        t = 10;
        return check < 0.f;
    }

	void get_surface_data(const Point&, Point& hit_normal, Vec2f&) const {
		hit_normal = { 0.f, 0.f, -1.f };
	}
};

struct Sphere : public Object {
	using Vec3f = alpha::math::Vec3f;

	Vec3f center;
	float radius;

	Sphere() : center(0.f, 0.f, 0.f), radius(1.f) {}
	Sphere(float cx, float cy, float cz, float r) : center(cx, cy, cz), radius(r) {}
	Sphere(Vec3f c, float r) : center(c), radius(r) {}

	bool intersect(const Ray& cam_ray, float& t) const {
		const auto& o = cam_ray.origin;
		const auto& d = cam_ray.dir;

		auto p = o - center;

		float a = d.norm();
		float b = 2 * p.dot_product(d);
		float c = p.norm() - radius * radius;

		auto res = math::solve_quadratic(a, b, c);

		if (res.first == false) return res.first;

		auto& ts = res.second;

		if (ts.x > ts.y) std::swap(ts.x, ts.y);

		if (ts.x < 0) {
			ts.x = ts.y;

			if (ts.x < 0) return false;
		}

		t = ts.x;

		return res.first;
	}

	void get_surface_data(const Point& hit_point, Point& hit_normal, Vec2f& tex) const {
		hit_normal = hit_point - center;
		hit_normal.normalize();

		// Create texture co-ordinates.
		tex.x = (1.f + atan2f(hit_normal.z, hit_normal.x) / (float) M_PI) * 0.5f;
		tex.y = acosf(hit_normal.y) / (float) M_PI;
	}
};

};
}

#endif
