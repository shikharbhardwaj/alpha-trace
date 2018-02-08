#include "cow.hpp"
#include <alpha/math.hpp>
typedef struct render_triangle {
    using Vec3f = alpha::math::Vec3f;
    using Vec2f = alpha::math::Vec2f;
    static int id;

    Vec3f operator()(float b0, float b1, float b2, float z, Vec3f v0_cam,
                     Vec3f v1_cam, Vec3f v2_cam) {
        alpha::math::Vec2f st0 = st[stindices[id * 3]];
        alpha::math::Vec2f st1 = st[stindices[id * 3 + 1]];
        alpha::math::Vec2f st2 = st[stindices[id * 3 + 2]];
        st0 *= (-1.f / v0_cam[2]);
        st1 *= (-1.f / v1_cam[2]);
        st2 *= (-1.f / v2_cam[2]);
        Vec2f st = st0 * b0 + st1 * b1 + st2 * b2;
        st = st * z;
        float px = (v0_cam[0] / -v0_cam[2]) * b0 + (v1_cam[0] / -v1_cam[2]) * b1 +
                   (v2_cam[0] / -v2_cam[2]) * b2;
        float py = (v0_cam[1] / -v0_cam[2]) * b0 + (v1_cam[1] / -v1_cam[2]) * b1 +
                   (v2_cam[1] / -v2_cam[2]) * b2;
        alpha::math::Vec3f pt(px * z, py * z, -z); // In camera space
        Vec3f normal, v1_sub = v1_cam - v0_cam, v2_sub = v2_cam - v0_cam;

        gmtl::cross(normal, v1_sub, v2_sub);

        gmtl::normalize(normal);

        Vec3f view_dir = pt * -1.f;
        gmtl::normalize(view_dir);

        float n_dot_alpha = gmtl::dot(normal, view_dir);
        if (n_dot_alpha < 0.f) {
            return Vec3f(0, 0, 0);
        }
        // Culling threshold = 0.5deg
        const float back_face_culling_threshold = 0.99996192306;
        if (n_dot_alpha > back_face_culling_threshold) {
            return Vec3f(0, 0, 0);
        }
        // This is the value of "intensity" ratio, which is to
        // be multiplied with the original color at the point to
        // obtain the final shade, when viewed at the current
        // perspective

        // Generate the checkerboard pattern
        const int M = 100;
        float checker =
            (fmod(st[0] * M, 1.0) > 0.5) ^ (fmod(st[1] * M, 1.0) < 0.5);
        float c = 0.3 * (1 - checker) + 0.7 * checker;
        return Vec3f(255 * c * n_dot_alpha, 255 * c * n_dot_alpha,
                     255 * c * n_dot_alpha);
    }
} render_triangle;
