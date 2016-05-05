#include <rasteriser_alpha.hpp>
int main() {
    // Render a cube from a perspective
    const alpha::math::Matrix44f world_to_cam{
        {0.6859, 0.7276, -0.0108, -0.3382},
        {-0.3174, 0.3125, 0.8953, -0.3767},
        {0.6549, -0.6107, 0.4452, -11.2523},
        {0.0000, 0.0000, 0.0000, 1.0000}};
    const int img_width = 640, img_height = 480;
    float aperture_width = 0.980, aperture_height = 0.735;
    float z_near = 1, z_far = 1000, focal_length = 20;
    auto cam_inst = std::make_shared<alpha::Camera>(
        img_width, img_height, aperture_width, aperture_height, z_near, z_far,
        focal_length, world_to_cam);
    alpha::Rasteriser rast(cam_inst, 255);
    // Now render the cube
    std::vector<alpha::math::Vec3f> vertices = {
        {1.000000, -1.000000, -1.000000},
        {1.000000, -1.000000, 1.000000},
        {-1.000000, -1.000000, 1.000000},
        {-1.000000, -1.000000, -1.000000},
        {1.000000, 1.000000, -0.999999},
        {0.999999, 1.000000, 1.000001},
        {-1.000000, 1.000000, 1.000000},
        {-1.000000, 1.000000, -1.000000}

    };
    // What should the shader triangles be?
    alpha::math::Vec2f shader = {0.5, 0.5};
    rast.draw_triangle(vertices[0], vertices[1], vertices[2], shader, shader,
                       shader);
    rast.draw_triangle(vertices[3], vertices[4], vertices[5], shader, shader,
                       shader);
    rast.dump_as_ppm("cube.ppm");
}
