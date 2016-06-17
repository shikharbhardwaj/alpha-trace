//
// TODO: Render the polygon mesh
//
#include "cow.hpp"
#include <buffers_alpha.hpp>
#include <fstream>
#include <iostream>
#include <math_alpha.hpp>
#include <rasteriser_alpha.hpp>

// Setup view
const int width = 4 * 640, height = 4 * 480, z_near = 1, z_far = 1000,
          focal_length = 20;
const float aperture_width = 0.980, aperture_height = 0.735;
auto cam_inst = std::make_shared<alpha::Camera>(
    width, height, aperture_width, aperture_height, z_near, z_far, focal_length,
    std::initializer_list<std::initializer_list<float>>{
        {0.707107, -0.331295, 0.624695, 0},
        {0, 0.883452, 0.468521, 0},
        {-0.707107, -0.331295, 0.624695, 0},
        {-1.63871, -5.747777, -40.400412, 1},
    });
// Send a line to the SVG
void put_line(const alpha::math::Vec3f &first, const alpha::math::Vec3f &sec,
              std::ofstream &ofs) {
    ofs << "<line x1='" << (int)first.x << "' y1 = '" << (int)first.y
        << "' x2 = '" << (int)sec.x << "' y2 ='" << (int)sec.y << "'/>\n";
}
alpha::Rasteriser<> rast(cam_inst);
int main() {
    std::cout << "Rendering polygon mesh to .svg file";
    std::ofstream ofs("out.svg");
    ofs << "<svg version=\"1.1\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" "
           "xmlns=\"http://www.w3.org/2000/svg\" height=\""
        << height << "\" width=\"" << width << "\">" << std::endl;
    ofs << "<style> line{stroke:rgb(0, 0, 0); stroke-width:0.2;} </style>\n";

    int num_tris = 3156;
    for (int i = 0; i < num_tris; i++) {
        const alpha::math::Vec3f &v0 = vertices[nvertices[i * 3]];
        const alpha::math::Vec3f &v1 = vertices[nvertices[i * 3 + 1]];
        const alpha::math::Vec3f &v2 = vertices[nvertices[i * 3 + 2]];
        alpha::math::Vec3f v0_rast;
        alpha::math::Vec3f v1_rast;
        alpha::math::Vec3f v2_rast;
        cam_inst->convert_to_raster(v0, v0_rast);
        cam_inst->convert_to_raster(v1, v1_rast);
        cam_inst->convert_to_raster(v2, v2_rast);
        put_line(v0_rast, v1_rast, ofs);
        put_line(v1_rast, v2_rast, ofs);
        put_line(v2_rast, v0_rast, ofs);
    }
    ofs << "</svg>\n";
    std::cout << "\nDone. \n";
    ofs.close();
}
