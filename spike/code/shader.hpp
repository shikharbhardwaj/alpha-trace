#include "cow.hpp"
#include <alpha/buffers.hpp>
#include <alpha/math.hpp>

typedef struct render_triangle {
    using Vec3f = alpha::math::Vec3f;
    using Vec2f = alpha::math::Vec2f;
    static int id;

    alpha::buffers::RGB operator()(float b0, float b1, float b2, float z,
        Vec3f v0_cam, Vec3f v1_cam, Vec3f v2_cam) {
        Vec2f& st0 = (st[stindices[id * 3]]);
        Vec2f& st1 = (st[stindices[id * 3 + 1]]);
        Vec2f& st2 = (st[stindices[id * 3 + 2]]);

        float z0 = -z / v0_cam.z;
        float z1 = -z / v1_cam.z;
        float z2 = -z / v2_cam.z;

        Vec2f st_cam = st0 * b0 * z0 + st1 * b1 * z1 + st2 * b2 * z2;

        float px = (v0_cam.x / -v0_cam.z) * b0 + (v1_cam.x / -v1_cam.z) * b1 +
                   (v2_cam.x / -v2_cam.z) * b2;
        float py = (v0_cam.y / -v0_cam.z) * b0 + (v1_cam.y / -v1_cam.z) * b1 +
                   (v2_cam.y / -v2_cam.z) * b2;

        auto normal = (v1_cam - v0_cam).cross_product(v2_cam - v0_cam);
        normal.normalize();

        Vec3f view_dir(-px * z, -py * z, z);
        view_dir.normalize();

        float n_dot_alpha = normal.dot_product(view_dir);
        if (n_dot_alpha < 0.f) {
            return alpha::buffers::RGB(0, 0, 0);
        }
        // Culling threshold = 0.5deg
        //const float back_face_culling_threshold = 0.99996192306;
        //if (n_dot_alpha > back_face_culling_threshold) {
            //return alpha::buffers::RGB(0, 0, 0);
        //}
        // This is the value of "intensity" ratio, which is to
        // be multiplied with the original color at the point to
        // obtain the final shade, when viewed at the current
        // perspective

        // Generate the checkerboard pattern
        const int M = 10;
        float checker =
            static_cast<float>((fmod(st_cam.x * M, 1.0) > 0.5) ^ (fmod(st_cam.y * M, 1.0) < 0.5));
        uint8_t c = static_cast<uint8_t>((0.3f * (1 - checker) + 0.7f * checker) * n_dot_alpha);
        return alpha::buffers::RGB(255 * c, 255 * c, 255 * c);
    }
} render_triangle;
