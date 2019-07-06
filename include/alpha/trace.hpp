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
				auto ray = cam->get_camera_ray(i, j);

				for (auto& obj_ptr : scene) {
					float t;

					auto& object = *obj_ptr.get();

					// Check for intersection.
					// TODO: Shading, lighting, effects etc.
					if (object.intersect(ray, t) == true) {
						Fbuf->set(i, j, object.color.x, object.color.y, object.color.z);
					} else {
						Fbuf->set(i, j, 0, 0, 0);
					}
				}
			}
		}
	}
};
} // namespace alpha

#endif // !TRACE_ALPHA_HPP
