//
// TODO: Render the polygon mesh
//
#include "cow.hpp"
#include <fstream>
#include <iostream>

#include <alpha/rasteriser.hpp>
#include <alpha/svg.hpp>

// Setup view
const int width = 4 * 640, height = 4 * 480;
const float z_near = 1.f, z_far = 1000.f, focal_length = 20.f;
const float aperture_width = 0.980f, aperture_height = 0.735f;
alpha::math::Matrix44f world2cam({
    0.707107f, -0.331295f, 0.624695f, 0.f,
    0.f, 0.883452f, 0.468521f, 0.f,
    -0.707107f, -0.331295f, 0.624695f, 0.f,
    -1.63871f, -5.747777f, -40.400412f, 1.f,
});
auto cam_inst = std::make_shared<alpha::Camera>(
    width, height, aperture_width, aperture_height, z_near, z_far, focal_length,
    world2cam);
// Send a line to the SVG
void put_line(const alpha::math::Vec3f &first, const alpha::math::Vec3f &sec,
              std::ofstream &ofs) {
    ofs << "<line x1='" << (int)first.x << "' y1 = '" << (int)first.y
        << "' x2 = '" << (int)sec.x << "' y2 ='" << (int)sec.y << "'/>\n";
}
alpha::Rasteriser<> rast(cam_inst);
int main() {
    std::cout << "Rendering polygon mesh to .svg file";
    alpha::SVG_export svg(width, height, "name.svg");
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
        svg.put_line(v0_rast, v1_rast);
        svg.put_line(v1_rast, v2_rast);
        svg.put_line(v2_rast, v0_rast);
    }
    std::cout << "\nDone. \n";
}
