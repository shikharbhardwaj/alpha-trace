// Implement the simplest form of the rasterisation algorithm
//
// Computing the bounding box of a number of triangles
#include <math_alpha.hpp>
#include <prettyprint.hpp>
typedef struct tri { int v[3]; } tri;
int img_width;
int img_height;
tri triangle[3];
float project_and_convert_to_NDC(float);
std::pair<alpha::Vec2f, alpha::Vec2f> compute_bounding_box() {
    std::pair<alpha::Vec2f, alpha::Vec2f> bounding_box;
    auto &bbmin = bounding_box.first;
    auto &bbmax = bounding_box.second;
    alpha::Vec2f vertice_projection[3];
    for (int i = 0; i < 3; ++i) {
        vertice_projection[i] = project_and_convert_to_NDC(triangle[i].v[i]);
        vertice_projection[i].x *= img_width;
        vertice_projection[i].y *= img_height;
        if (vertice_projection[i].x < bbmin.x) {
            bbmin.x = vertice_projection[i].x;
        }
        if (vertice_projection[i].y < bbmin.y) {
            bbmin.y = vertice_projection[i].y;
        }
        if (vertice_projection[i].x > bbmax.x) {
            bbmax.x = vertice_projection[i].x;
        }
        if (vertice_projection[i].y > bbmax.y) {
            bbmax.y = vertice_projection[i].y;
        }
    }
    return bounding_box;
}
int main() {}
