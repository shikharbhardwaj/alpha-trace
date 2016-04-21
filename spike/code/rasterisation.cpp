// Implement the simplest form of the rasterisation algorithm
#include <math_alpha.hpp>
#include <ppm_alpha.hpp>
#include <prettyprint.hpp>
using namespace alpha;
float edge_function(const Vec2f &a, const Vec2f &b, const Vec2f &c) {
    return ((b.y - a.y) * (c.x - a.x) - (b.x - a.x) * (c.y - a.y));
}
int main() {
    const int img_width = 1366;
    const int img_height = 768;
    alpha::Vec2f v0(0, 0);
    alpha::Vec2f v1(0, img_height);
    alpha::Vec2f v2(img_width, img_height);
    alpha::Vec3f c0(1, 0, 0);
    alpha::Vec3f c1(0, 1, 0);
    alpha::Vec3f c2(0, 0, 1);
    alpha::ppm_image out("2draster.ppm", img_height, img_width);
    float area = edge_function(v0, v1, v2);
    std::cout << "\nArea : " << area << std::endl;
    for (int j = 0; j < img_height; j++) {
        for (int i = 0; i < img_width; i++) {
            alpha::Vec2f p(i + .16f, j + 0.9f);
            float w0 = edge_function(v1, v2, p);
            float w1 = edge_function(v2, v0, p);
            float w2 = edge_function(v0, v1, p);
            if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
                // The point is visible
                w0 /= area;
                w1 /= area;
                w2 /= area;
                // Compute contribution of each vertex
                Vec3i color;
                color.x = w0 * 255;
                color.y = w1 * 255;
                color.z = w2 * 255;
                out.set(i, j, color);
            }
        }
    }
    out.dump();
}
