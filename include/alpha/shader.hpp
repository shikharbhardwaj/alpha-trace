#include <math_alpha.hpp>

namespace alpha{
typedef struct render_triangle {
    int id = 0;

    math::Vec3f operator()(float b0, float b1, float b2, float z,
        math::Vec3f v0_cam, math::Vec3f v1_cam, math::Vec3f v2_cam) {
        math::Vec2f st0 = st[stindices[id * 3]];
        math::Vec2f st1 = st[stindices[id * 3 + 1]];
        math::Vec2f st2 = st[stindices[id * 3 + 2]];
        st0 = st0 * (-1.f / v0_cam.z);
        st1 = st1 * (-1.f / v1_cam.z);
        st2 = st2 * (-1.f / v2_cam.z);
        Vec2f st = st0 * b0 + st1 * b1 + st2 * b2;
        st = st * z;
        float px = (v0_cam.x / -v0_cam.z) * b0 + (v1_cam.x / -v1_cam.z) * b1 +
                   (v2_cam.x / -v2_cam.z) * b2;
        float py = (v0_cam.y / -v0_cam.z) * b0 + (v1_cam.y / -v1_cam.z) * b1 +
                   (v2_cam.y / -v2_cam.z) * b2;
        alpha::math::Vec3f pt(px * z, py * z, -z); // In camera space
        auto normal = (v1_cam - v0_cam).cross_product(v2_cam - v0_cam);
        normal.normalize();
        Vec3f view_dir = pt * -1.f;
        view_dir.normalize();
        float n_dot_alpha = normal.dot_product(view_dir);
        if (n_dot_alpha < 0.f) {
            return Vec3f(0, 0, 0);
        }
        // Culling threshold = 0.5deg
        const float back_face_culling_threshold = 0.99996192306;
        if (n_dot_alpha / (normal.length() * view_dir.length()) >
            back_face_culling_threshold) {
            return Vec3f(0, 0, 0);
        }
        // This is the value of "intensity" ratio, which is to
        // be multiplied with the original color at the point to
        // obtain the final shade, when viewed at the current
        // perspective

        // Generate the checkerboard pattern
        const int M = 10;
        float checker =
                (fmod(st.x * M, 1.0) > 0.5) ^(fmod(st.y * M, 1.0) < 0.5);
        float c = 0.3 * (1 - checker) + 0.7 * checker;
        return Vec3f(255 * c * n_dot_alpha, 255 * c * n_dot_alpha,
                     255 * c * n_dot_alpha);
    }
} render_triangle;
}
