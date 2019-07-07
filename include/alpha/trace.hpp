//===-- trace.hpp --------- Ray tracing routines ----------------*- C++ -*-===//
//
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
///  Implement ray tracing
///
//===----------------------------------------------------------------------===//
#ifndef TRACE_ALPHA_HPP
#define TRACE_ALPHA_HPP

#include <vector>
#include <memory>

#include <alpha/camera.hpp>
#include <alpha/objects.hpp>
#include <alpha/buffers.hpp>

namespace alpha {
using Scene = std::vector<std::shared_ptr<objects::Object>>;

class Tracer {
	using Object = alpha::objects::Object;
	using RGB = alpha::buffers::RGB;
	using Vec3f = alpha::math::Vec3f;

	std::shared_ptr<Camera> cam;
	std::unique_ptr<buffers::Imagebuffer> Fbuf;
	uint32_t width, height;

public:
	Tracer() = delete;
	Tracer(std::shared_ptr<Camera> _cam_inst) {
		cam = _cam_inst;
		width = cam->img_width;
		height = cam->img_height;
		Fbuf = std::make_unique<buffers::Imagebuffer>(width, height);
	}

	void dump_as_ppm(const std::string& name) { Fbuf->dump_as_ppm(name); }

	void trace(const Scene &scene) {
		for (uint32_t j = 0; j < height; ++j) {
			for (uint32_t i = 0; i < width; ++i) {
				// Generate camera ray for this pixel.
				auto ray = cam->get_camera_ray(i, j);

				// Background color.
				const buffers::RGB bg_color = { 0, 0, 0 };

				// Far clipping.
				float besthit = 1000;

				// Check which object hit.
				const Object* hit_obj = nullptr;

				for (auto& obj_ptr : scene) {
					float t;

					// Check for intersection.
					// TODO: Shading, lighting, effects etc.
					if (obj_ptr->intersect(ray, t) == true && t < besthit) {
						hit_obj = obj_ptr.get();
						besthit = t;
					}
				}

				if (hit_obj != nullptr) {
					// Get color from the object.
					auto hit_point = ray.origin + ray.dir * besthit;
					Vec3f hit_normal;
					math::Vec2f tex;

					hit_obj->get_surface_data(hit_point, hit_normal, tex);
					float scale = 4.f;
					float pattern = (float) ((fmodf(tex.x * scale, 1.f) > 0.5f) ^ (fmodf(tex.y * scale, 1.f) > 0.5f));

					// Color mixing
					Vec3f colorf = buffers::fp_color(hit_obj->color);
					colorf = buffers::mix(colorf, colorf * 0.8f, pattern) * std::max(0.f,
						hit_normal.dot_product(ray.dir * -1.f));
					RGB final_color = buffers::int_color(colorf);
					Fbuf->set(i, j, final_color.r, final_color.g, final_color.b);
				} else {
					Fbuf->set(i, j, bg_color.r, bg_color.g, bg_color.b);
				}
			}
		}
	}
};
} // namespace alpha

#endif // !TRACE_ALPHA_HPP
