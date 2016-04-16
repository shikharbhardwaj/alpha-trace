// Implement an ideal pinhole camera
#include <iostream>
#include <math_alpha.hpp>
#include <graphics_alpha.hpp>
// Object data begin
// Vertices making up the object
const Vec3f verts[146] = {{-2.5703, 0.78053, -2.4e-05},
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
// The triangles
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
float film_aperture_width = 0.825;
float film_aperture_height = 0.446;
static const float inch_to_mm = 25.4;
float z_near = 0.1;
float z_far = 1000;
// Camera state end
// Image info
uint32_t img_width = 512;
uint32_t img_height = 512;
// Resolution gate strategy
enum class fit_resolution_gate { Fill = 0, Overscan };
fit_resolution_gate fit_film = fit_resolution_gate::Overscan;
int main() {
    // Scan each vertex, project onto screen and color red if if goes out of
    // screen
}
