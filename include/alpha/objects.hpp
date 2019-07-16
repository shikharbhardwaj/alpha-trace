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

struct Sphere : public Object {
	Point center;
	float radius;

	Sphere() = default;
	Sphere(float cx, float cy, float cz, float r) : center(cx, cy, cz), radius(r) {}
	Sphere(Point c, float r) : center(c), radius(r) {}

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

struct Plane : public Object {
	Point n, p;

	Plane() = default;
	Plane(const Point& normal, const Point& point) : n(normal), p(point) {}

	bool intersect(const Ray& cam_ray, float& t) const {
		const auto& o = cam_ray.origin;
		const auto& dir = cam_ray.dir;

		float denom = dir.dot_product(n);

		if (denom < 1e-6) return false;

		auto tr_o = (p - o).dot_product(n);
		t = tr_o / denom;

		return t >= 0.f;
	}

	void get_surface_data(const Point& hit_point, Point& hit_normal, Vec2f& tex) const {
		hit_normal = n * -1.f;

		// Repeating texture co-ordinates.
		tex.x = fmod(fabs(hit_point.x - p.x), 1.f);
		tex.y = fmod(fabs(hit_point.y - p.y), 1.f);
	}
};

struct Disk : public Object {
	Point n, c;

	float r;

	Disk() = default;
	Disk(const Point& normal, const Point& center, float radius) : n(normal), c(center), r(radius) {}

	bool get_hitpoint(const Ray& cam_ray, Point& hit_point, float& t) const {
		const auto& o = cam_ray.origin;
		const auto& dir = cam_ray.dir;

		float denom = dir.dot_product(n);

		if (denom < 1e-6) return false;

		auto tr_o = (c - o).dot_product(n);
		float t0 = tr_o / denom;

		hit_point = o + dir * t0;

		if ((c - hit_point).norm() > r) return false;

		t = t0;

		return true;
	}


	bool intersect(const Ray& cam_ray, float& t) const {
		Point hit_point;
		return get_hitpoint(cam_ray, hit_point, t);
	}

	void get_surface_data(const Point& hit_point, Point& hit_normal, Vec2f& tex) const {
		hit_normal = n * -1.f;

		// Repeating texture co-ordinates.
		tex.x = fmod(fabs(hit_point.x - c.x), 1.f);
		tex.y = fmod(fabs(hit_point.y - c.y), 1.f);
	}
};

struct AABB : public Object {
	Point bounds[2];

	AABB() = default;
	AABB(const Point& min, const Point& max) {
		bounds[0] = min;
		bounds[1] = max;
	}

	bool intersect(const Ray& cam_ray, float& t) const {
		const auto& o = cam_ray.origin;
		const auto& d = cam_ray.dir;

		float tmin_x = (bounds[0].x - o.x) / d.x;
		float tmax_x = (bounds[1].x - o.x) / d.x;

		if (tmin_x > tmax_x) std::swap(tmin_x, tmax_x);

		float tmin_y = (bounds[0].y - o.y) / d.y;
		float tmax_y = (bounds[1].y - o.y) / d.y;

		if (tmin_y > tmax_y) std::swap(tmin_y, tmax_y);

		float tmin_z = (bounds[0].z - o.z) / d.z;
		float tmax_z = (bounds[1].z - o.z) / d.z;

		if (tmin_z > tmax_z) std::swap(tmin_z, tmax_z);

		// Intersect the three ranges.
		float tmin = math::max_3(tmin_x, tmin_y, tmin_z);
		float tmax = math::min_3(tmax_x, tmax_y, tmax_z);

		t = tmin;

		return tmin <= tmax;
	}

	void get_surface_data(const Point& hit_point, Point& hit_normal, Vec2f& tex) const {
		// { 0,  0,  1} -> z = zmax
		// { 0,  0, -1} -> z = zmin
		// { 0,  1,  0} -> x = xmax
		// { 0, -1,  0} -> x = xmin
		// { 1,  0,  0} -> y = ymax
		// {-1,  0,  0} -> y = ymin

		hit_normal = { 0.f, 0.f, 0.f };
		if (hit_point.z == bounds[0].z) {
			hit_normal.z = -1.f;
			tex.x = (hit_point.x - bounds[0].x) / (bounds[1].x - bounds[0].x);
			tex.y = (hit_point.y - bounds[0].y) / (bounds[1].y - bounds[0].y);
		}
		else if (hit_point.z == bounds[1].z) {
			hit_normal.z = 1.f;
			tex.x = (hit_point.x - bounds[0].x) / (bounds[1].x - bounds[0].x);
			tex.y = (hit_point.y - bounds[0].y) / (bounds[1].y - bounds[0].y);
		}
		else if (hit_point.y == bounds[0].y) {
			hit_normal.y = -1.f;
			tex.x = (hit_point.z - bounds[0].z) / (bounds[1].z - bounds[0].z);
			tex.y = (hit_point.y - bounds[0].y) / (bounds[1].y - bounds[0].y);
		}
		else if (hit_point.y == bounds[1].y) {
			hit_normal.y = 1.f;
			tex.x = (hit_point.z - bounds[0].z) / (bounds[1].z - bounds[0].z);
			tex.y = (hit_point.y - bounds[0].y) / (bounds[1].y - bounds[0].y);
		}
		else if (hit_point.x == bounds[0].x) {
			hit_normal.x = -1.f;
			tex.x = (hit_point.x - bounds[0].x) / (bounds[1].x - bounds[0].x);
			tex.y = (hit_point.z - bounds[0].z) / (bounds[1].z - bounds[0].z);
		}
		else if (hit_point.x == bounds[1].x) {
			hit_normal.x = 1.f;
			tex.x = (hit_point.x - bounds[0].x) / (bounds[1].x - bounds[0].x);
			tex.y = (hit_point.z - bounds[0].z) / (bounds[1].z - bounds[0].z);
		}
	}
};

}; // namespace objects
} // namespace alpha

#endif
