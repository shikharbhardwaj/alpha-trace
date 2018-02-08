//===---- vertex_import ------ Vertex data import ---------------*- C++ -*-===//
//
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Import vertex data from disk to memory
///
//===----------------------------------------------------------------------===//
#ifndef ALPHA_VERTEX
#define ALPHA_VERTEX

#include <fstream>
#include <vector>

#include <alpha/math.hpp>

namespace alpha {
typedef struct mesh_data {
    uint32_t num_triangles;
    std::vector<alpha::math::Vec3f> vertices;

    mesh_data() = delete;

    mesh_data(const std::string &src_name, bool y_up = false,
              uint32_t n_tri = 0) {
        vertices.reserve(n_tri);
        std::ifstream handle(src_name);
        while (!handle.eof()) {
            float x, y, z;
            if (y_up) {
                handle >> x >> z >> y;
            } else {
                handle >> x >> y >> z;
            }
            vertices.emplace_back(alpha::math::Vec3f(x, y, z));
        }
        handle.close();
        num_triangles = vertices.size() / 3;
    }
} mesh_data;
}
#endif
