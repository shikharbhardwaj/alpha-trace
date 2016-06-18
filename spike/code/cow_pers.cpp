#include "cow_vert.hpp"
#include <math_alpha.hpp>
#include <rasteriser_alpha.hpp>
int numtris = 3156;
void put_line(const alpha::math::Vec3f &first, const alpha::math::Vec3f &sec,
              std::ofstream &ofs) {
    ofs << "<line x1='" << (int)first.x << "' y1 = '" << (int)first.y
        << "' x2 = '" << (int)sec.x << "' y2 ='" << (int)sec.y << "'/>\n";
}

int main() {
    // Render a cube from a perspective
    std::cout << "Rendering polygon mesh to .svg file";
    std::ofstream ofs("out.svg");
    const int width = 1920, height = 1080;
    ofs << "<svg version=\"1.1\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" "
           "xmlns=\"http://www.w3.org/2000/svg\" height=\""
        << height << "\" width=\"" << width << "\">" << std::endl;
    ofs << "<style> line{stroke:rgb(0, 0, 0); stroke-width:0.2;} </style>\n";

    alpha::math::Matrix44f world_to_cam{
        {0.7071067690849304, -0.5, 0.5, 3.0206594467163086},
        {0.0, 0.7071067690849304, 0.7071067690849304, 5.744779586791992},
        {0.7071067690849304, 0.4999999701976776, -0.5, -3.3517706394195557},
        {0.0, 0.0, 0.0, 1.0}};
    world_to_cam.invert();
    world_to_cam.transpose();
    float aperture_width = 0.980, aperture_height = 0.735;
    float z_near = 0.1, z_far = 100, focal_length = 35.f;
    auto cam_inst = std::make_shared<alpha::Camera>(
        width, height, aperture_width, aperture_height, z_near, z_far,
        focal_length, world_to_cam);
    alpha::Rasteriser<> rast(cam_inst);
    // Now render the cube
    for (int i = 0; i < numtris; i++) {
        const auto v0 = vertices[3 * i];
        const auto v1 = vertices[3 * i + 1];
        const auto v2 = vertices[3 * i + 2];
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
