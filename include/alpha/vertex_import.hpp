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
#include <iostream>
#include <stdexcept>

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

        if (!handle.is_open()) {
            throw std::invalid_argument("Could not find mesh data file " + src_name);
        }

        while (handle) {
            float x, y, z;
            if (y_up) {
                handle >> x >> z >> y;
            } else {
                handle >> x >> y >> z;
            }
            vertices.emplace_back(alpha::math::Vec3f(x, y, z));
        }
        handle.close();
        num_triangles = (uint32_t) vertices.size() / 3;
#ifdef ALPHA_DEBUG
        std::cout << "Read " << num_triangles << " triangles from file " << src_name << std::endl;
#endif
    }
} mesh_data;
}
#endif
