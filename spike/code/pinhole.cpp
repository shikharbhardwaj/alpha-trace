// Implement an ideal pinhole camera
#include <iostream>
#include <fstream>
#include <math_alpha.hpp>
#include <graphics_alpha.hpp>
#include <prettyprint.hpp>
// Object data begin
// Vertices making up the object
const alpha::Vec3f verts[146] = {{-2.5703, 0.78053, -2.4e-05},
                                 {-0.89264, 0.022582, 0.018577},
                                 {1.6878, -0.017131, 0.022032},
                                 {3.4659, 0.025667, 0.018577},
                                 {-2.5703, 0.78969, -0.001202},
                                 {-0.89264, 0.25121, 0.93573},
                                 {1.6878, 0.25121, 1.1097},
                                 {3.5031, 0.25293, 0.93573},
                                 {-2.5703, 1.0558, -0.001347},
                                 {-0.89264, 1.0558, 1.0487},
                                 {1.6878, 1.0558, 1.2437},
                                 {3.6342, 1.0527, 1.0487},
                                 {-2.5703, 1.0558, 0},
                                 {-0.89264, 1.0558, 0},
                                 {1.6878, 1.0558, 0},
                                 {3.6342, 1.0527, 0},
                                 {-2.5703, 1.0558, 0.001347},
                                 {-0.89264, 1.0558, -1.0487},
                                 {1.6878, 1.0558, -1.2437},
                                 {3.6342, 1.0527, -1.0487},
                                 {-2.5703, 0.78969, 0.001202},
                                 {-0.89264, 0.25121, -0.93573},
                                 {1.6878, 0.25121, -1.1097},
                                 {3.5031, 0.25293, -0.93573},
                                 {3.5031, 0.25293, 0},
                                 {-2.5703, 0.78969, 0},
                                 {1.1091, 1.2179, 0},
                                 {1.145, 6.617, 0},
                                 {4.0878, 1.2383, 0},
                                 {-2.5693, 1.1771, -0.081683},
                                 {0.98353, 6.4948, -0.081683},
                                 {-0.72112, 1.1364, -0.081683},
                                 {0.9297, 6.454, 0},
                                 {-0.7929, 1.279, 0},
                                 {0.91176, 1.2994, 0}};
// Number of triangles in object
const uint32_t num_tris = 51;
// The indexes of vertices making up the triangles
const uint32_t tris[num_tris * 3] = {
    4,  0,  5,  0,  1,  5,  1,  2,  5,  5,  2,  6,  3,  7,  2,  2,  7,
    6,  5,  9,  4,  4,  9,  8,  5,  6,  9,  9,  6,  10, 7,  11, 6,  6,
    11, 10, 9,  13, 8,  8,  13, 12, 10, 14, 9,  9,  14, 13, 10, 11, 14,
    14, 11, 15, 17, 16, 13, 12, 13, 16, 13, 14, 17, 17, 14, 18, 15, 19,
    14, 14, 19, 18, 16, 17, 20, 20, 17, 21, 18, 22, 17, 17, 22, 21, 18,
    19, 22, 22, 19, 23, 20, 21, 0,  21, 1,  0,  22, 2,  21, 21, 2,  1,
    22, 23, 2,  2,  23, 3,  3,  23, 24, 3,  24, 7,  24, 23, 15, 15, 23,
    19, 24, 15, 7,  7,  15, 11, 0,  25, 20, 0,  4,  25, 20, 25, 16, 16,
    25, 12, 25, 4,  12, 12, 4,  8,  26, 27, 28, 29, 30, 31, 32, 34, 33};
// Object data end

// Camera state begin
float focal_length = 35; // mm
// 35mm full aperture
float film_aperture_width = 1.995;
float film_aperture_height = 1.500;
static const float inch_to_mm = 25.4;
float z_near = 0.1;
float z_far = 1000;
// Camera state end
// Image info
uint32_t img_width = 640;
uint32_t img_height = 480;
// Resolution gate strategy
enum class fit_resolution_gate { Fill = 0, Overscan };
fit_resolution_gate fit_film = fit_resolution_gate::Overscan;
int main() {
    // Scan each vertex, project onto screen and color red if if goes out of
    // screen
    float film_aspect_ratio = film_aperture_width / film_aperture_height;
    float device_aspect_ratio = img_width / (float)img_height;
    float top =
        ((film_aperture_height * inch_to_mm / 2) / focal_length) * z_near;
    float right =
        ((film_aperture_width * inch_to_mm / 2) / focal_length) * z_near;
    // float right = top * film_aspect_ratio;
    float xscale = 1.f;
    float yscale = 1.f;
    switch (fit_film) {
    default: // The default case is fill
    case fit_resolution_gate::Fill:
        if (film_aspect_ratio > device_aspect_ratio) {
            xscale = device_aspect_ratio / film_aspect_ratio;
        } else {
            yscale = film_aspect_ratio / device_aspect_ratio;
        }
        break;
    case fit_resolution_gate::Overscan:
        if (film_aspect_ratio > device_aspect_ratio) {
            yscale = film_aspect_ratio / device_aspect_ratio;
        } else {
            xscale = device_aspect_ratio / film_aspect_ratio;
        }
    }
    right *= xscale;
    top *= yscale;
    float bottom = -top;
    float left = -right;
    std::cout << "Screen window co-ords\t\t:\t" << std::make_pair(bottom, left)
              << "\n\t\t\t\t\t" << std::make_pair(top, right) << std::endl;
    std::cout << "Film aspect ratio\t\t:\t" << film_aspect_ratio << std::endl;
    std::cout << "Device aspect ratio\t\t:\t" << device_aspect_ratio
              << std::endl;
    std::cout << "Angle of view\t\t\t:\t"
              << 2 * (atan(right / z_near)) * 180 / M_PI << "°" << std::endl;
    // Project the triangle vertices onto the plane
    std::ofstream ofs;
    ofs.open("./pinhole.svg");
    ofs << "<svg version =\"1.1\" "
        << "xmlns:xlink=\"http://www.w3.org/1999/xlink\" "
        << "xmlns=\"http://www.w3.org/2000/svg\" width=\"" << img_width
        << "\" height=\"" << img_height << "\">" << std::endl;
    // The camera to world matrix as exported
    alpha::Matrix44f cam_to_world{{-0.95424, 0, 0.299041, 0},
                                  {0.0861242, 0.95763, 0.274823, 0},
                                  {-0.28637, 0.288002, -0.913809, 0},
                                  {-3.734612, 7.610426, -14.152769, 1}};
    auto world_to_cam = cam_to_world.inverse();
    // Process each triangle and project
    for (uint32_t i = 0; i < num_tris; i++) {
        // Get the three vertices
        const auto &v01_world = verts[tris[i * 3]];
        const auto &v02_world = verts[tris[i * 3 + 1]];
        const auto &v03_world = verts[tris[i * 3 + 2]];
        alpha::Vec2i v01_raster, v02_raster, v03_raster;
        bool visible = true;
        visible &= alpha::compute_pixel_coords(
            v01_world, world_to_cam, bottom, left, top, right, z_near,
            img_width, img_height, v01_raster);
        visible &= alpha::compute_pixel_coords(
            v02_world, world_to_cam, bottom, left, top, right, z_near,
            img_width, img_height, v02_raster);
        visible &= alpha::compute_pixel_coords(
            v03_world, world_to_cam, bottom, left, top, right, z_near,
            img_width, img_height, v03_raster);
        int color_val = visible ? 0 : 255;
        ofs << "<line";
        ofs << "   x1 = \"" << v01_raster.x << "\" y1 = \"" << v01_raster.y
            << "\" x2 = \"" << v02_raster.x << "\" y2 = \"" << v02_raster.y
            << "\" style = \"stroke:rgb(" << color_val << ",0, 0); "
            << "stroke-width:1\" />\n";
        ofs << "<line";
        ofs << "   x1 = \"" << v02_raster.x << "\" y1 = \"" << v02_raster.y
            << "\" x2 = \"" << v03_raster.x << "\" y2 = \"" << v03_raster.y
            << "\" style = \"stroke:rgb(" << color_val << ",0, 0); "
            << "stroke-width:1\" />\n";
        ofs << "<line";
        ofs << "   x1 = \"" << v03_raster.x << "\" y1 = \"" << v03_raster.y
            << "\" x2 = \"" << v01_raster.x << "\" y2 = \"" << v01_raster.y
            << "\" style = \"stroke:rgb(" << color_val << ",0, 0); "
            << "stroke-width:1\" />\n";
    }
    ofs << "</svg>";
    ofs.close();
}
