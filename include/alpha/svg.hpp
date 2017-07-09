//===-------- SVG --------------- SVG exporter ------------------*- C++ -*-===//
//
// Alpha-trace -> Minimal C++ raytracer
//
// Written by: Shikhar Bhardwaj | shikhar@bluefog.me
//
//===----------------------------------------------------------------------===//
///
/// \file
/// Export vertices to an SVG
///
//===----------------------------------------------------------------------===//
#ifndef ALPHA_SVG
#define ALPHA_SVG

#include <fstream>

#include <alpha/math_alpha.hpp>

namespace alpha {
class SVG_export {
    uint32_t width, height;
    std::string file_name;
    std::ofstream handle;

public:
    SVG_export() = delete;

    SVG_export(uint32_t w, uint32_t h, const std::string &name)
            : width(w), height(h), file_name(name) {
        handle.open(name);
        if (handle.fail()) {
            std::cerr << "SVG export target failed to open";
            return;
        }
        handle << "<svg version=\"1.1\" "
                "xmlns:xlink=\"http://www.w3.org/1999/xlink\" "
                "xmlns=\"http://www.w3.org/2000/svg\" height=\""
               << height << "\" width=\"" << width << "\">" << std::endl;
        handle << "<style> line{stroke:rgb(0, 0, 0); stroke-width:0.2;} "
                "</style>\n";
    }

    void put_line(const alpha::math::Vec3f &first,
                  const alpha::math::Vec3f &sec) {
        handle << "<line x1='" << (int) first.x << "' y1 = '" << (int) first.y
               << "' x2 = '" << (int) sec.x << "' y2 ='" << (int) sec.y
               << "'/>\n";
    }

    ~SVG_export() {
        handle << "</svg>\n";
        handle.close();
    }
};
}
#endif
