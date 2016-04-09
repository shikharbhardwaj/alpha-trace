#include <math_alpha.hpp>
#include <ppm_alpha.hpp>
int main() {
    using point = alpha::Vec3f;
    const unsigned int img_height = 512, img_width = 512;
    alpha::ppm_image out("cube.ppm", img_height, img_width);
    alpha::Vec3i white(255, 255, 255);
    point corners[8] = {{1, -1, -5},
                        {1, -1, -3},
                        {1, 1, -5},
                        {1, 1, -3},
                        {-1, -1, -5},
                        {-1, -1, -3},
                        {-1, 1, -5},
                        {-1, 1, -3}};
    for (int i = 0; i < 8; i++) {
        auto x_proj = corners[i].x / -corners[i].z;
        auto y_proj = corners[i].y / -corners[i].z;
        auto x_proj_remap = (1 + x_proj) / 2;
        auto y_proj_remap = (1 + y_proj) / 2;
        auto x_proj_pix = x_proj_remap * img_width;
        auto y_proj_pix = y_proj_remap * img_height;
        std::cout << "The projected point with index [" << i << "] : ";
        std::cout << "(" << x_proj_pix << ", " << y_proj_pix << ")\n";
        out.set(x_proj_pix, y_proj_pix, white);
        out.set(x_proj_pix + 2, y_proj_pix + 2, white);
        out.set(x_proj_pix, y_proj_pix + 2, white);
        out.set(x_proj_pix + 2, y_proj_pix, white);
    }
    out.dump();
}
