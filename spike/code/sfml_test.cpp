#include "shader.hpp"
#include <chrono>
#include <memory>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <alpha/rasteriser.hpp>
#include <alpha/camera.hpp>
#include <alpha/math.hpp>

using namespace std;
using namespace alpha;

int render_triangle::id = 0;

const int width = 2 * 640, height = 2 * 480;

const float aperture_width = 0.980f, aperture_height = 0.735f, focal_length = 20, z_near = 1, z_far = 1000;
alpha::math::Matrix44f world2cam(
    { 0.707107f, -0.331295f, 0.624695f, 0.f,
            0.f,  0.883452f, 0.468521f, 0.f,
     -0.707107f, -0.331295f, 0.624695f, 0.f,
      -1.53871f, -5.747777f, -40.400412f, 1.f });
auto cam_inst = std::make_shared<alpha::Camera>(
    width, height, aperture_width, aperture_height, z_near, z_far, focal_length,
    world2cam);
render_triangle renderer;
alpha::Rasteriser<render_triangle> rast(cam_inst, renderer);
// Render the cow for me
const int num_tris = 3156;

int main() {

    sf::RenderWindow window(sf::VideoMode(width, height), "Software rasteriser demo");
    window.setFramerateLimit(30);

    sf::Uint8* pbuf = new sf::Uint8[width * height * 4];
    sf::Texture texture;

    texture.create(width, height);

    auto update_texture = [&]() {
        renderer.id = 0;
        rast.Fbuf->clear();
        rast.Zbuf->clear();
        for (int i = 0; i < num_tris; i++) {
            const alpha::math::Vec3f &v0 = vertices[nvertices[i * 3]];
            const alpha::math::Vec3f &v1 = vertices[nvertices[i * 3 + 1]];
            const alpha::math::Vec3f &v2 = vertices[nvertices[i * 3 + 2]];
            rast.draw_triangle(v0, v1, v2);
            renderer.id++;
        }
        // Copy pixels
        for (int i = 0; i < width * height * 4; i += 4) {
            int px = i / 4;
            int x = px % width;
            int y = px / width;
            auto color = rast.Fbuf->get(x, y);
            pbuf[i] = color.x;
            pbuf[i + 1] = color.y;
            pbuf[i + 2] = color.z;
            pbuf[i + 3] = 255;
        }
        texture.update(pbuf);
    };

    float delta = 0.05f;

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                alpha::math::Matrix44f scale_up({
                    1.0000f, 0.0000f, 0.0000f, 0.0000f,
                    0.0000f, 1.0000f, 0.0000f, 0.0000f,
                    0.0000f, 0.0000f, 2.0000f, 0.0000f,
                    0.0000f, 0.0000f, 0.0000f, 1.0000f,
                });
                alpha::math::Matrix44f scale_down({
                    1.0000f, 0.0000f, 0.0000f, 0.0000f,
                    0.0000f, 1.0000f, 0.0000f, 0.0000f,
                    0.0000f, 0.0000f, 0.5000f, 0.0000f,
                    0.0000f, 0.0000f, 0.0000f, 1.0000f,
                });
                
                alpha::math::Matrix44f rotatex_p({
                    1.0000f,  0.0000f,  0.0000f,  0.0000f,
                    0.0000f,  0.8660f,  0.5000f,  0.0000f,
                    0.0000f, -0.5000f,  0.8660f,  0.0000f,
                    0.0000f,  0.0000f,  0.0000f,  1.0000f,
                });

                alpha::math::Matrix44f rotatex_n({
                    1.0000f,  0.0000f,  0.0000f,  0.0000f,
                    0.0000f,  0.8660f, -0.5000f,  0.0000f,
                    0.0000f,  0.5000f,  0.8660f,  0.0000f,
                    0.0000f,  0.0000f,  0.0000f,  1.0000f,
                });

                alpha::math::Matrix44f rotatey_p({
                    0.8660f,  0.0000f, -0.5000f,  0.0000f,
                    0.0000f,  1.0000f,  0.0000f,  0.0000f,
                    0.5000f,  0.0000f,  0.8660f,  0.0000f,
                    0.0000f,  0.0000f,  0.0000f,  1.0000f,
                });

                alpha::math::Matrix44f rotatey_n({
                    0.8660f,  0.0000f,  0.5000f,  0.0000f,
                    0.0000f,  1.0000f,  0.0000f,  0.0000f,
                   -0.5000f,  0.0000f,  0.8660f,  0.0000f,
                    0.0000f,  0.0000f,  0.0000f,  1.0000f,
                });

                alpha::math::Matrix44f rotatez_p({
                    0.8660f, -0.5000f, 0.0000f, 0.0000f,
                    0.5000f, 0.8660f, 0.0000f, 0.0000f,
                    0.0000f, 0.0000f, 1.0000f, 0.0000f,
                    0.0000f, 0.0000f, 0.0000f, 1.0000f,
                });

                alpha::math::Matrix44f rotatez_n({
                    0.8660f, 0.5000f, 0.0000f, 0.0000f,
                    -0.5000f, 0.8660f, 0.0000f, 0.0000f,
                    0.0000f, 0.0000f, 1.0000f, 0.0000f,
                    0.0000f, 0.0000f, 0.0000f, 1.0000f,
                });

                alpha::math::Matrix44f rotate, scale;
                rotate.eye();
                scale.eye();

                float dx = 0.f, dy = 0.f, dz = 0.f;
                (void)dz;
                (void)dy;
                (void)dx;
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    break;
                } else if (event.key.code == sf::Keyboard::W) {
                    std::cout << "Scale up!" << endl;
                    scale = scale_up;
                } else if (event.key.code == sf::Keyboard::A) {
                    std::cout << "Move left!" << endl;
                    dy = -delta;
                } else if (event.key.code == sf::Keyboard::S) {
                    std::cout << "Scale down!" << endl;
                    scale = scale_down;
                } else if (event.key.code == sf::Keyboard::D) {
                    std::cout << "Move right!" << endl;
                    dy = delta;
                } else if (event.key.code == sf::Keyboard::Up) {
                    std::cout << "Rotate z+!" << endl;
                    rotate = rotatez_p;
                }else if (event.key.code == sf::Keyboard::Down) {
                    std::cout << "Rotate z-!" << endl;
                    rotate = rotatez_n;
                }else if (event.key.code == sf::Keyboard::Right) {
                    std::cout << "Rotate y+!" << endl;
                    rotate = rotatey_p;
                }else if (event.key.code == sf::Keyboard::Left) {
                    std::cout << "Rotate y-!" << endl;
                    rotate = rotatey_n;
                } else if (event.key.code == sf::Keyboard::Num0) {
                    std::wcout << "Reset view" << endl;
                    cam_inst->set_world_to_cam(world2cam);
                    cam_inst->compute_screen_coordinates();
                }
                (void)dx;

                auto w2cam = cam_inst->get_world_to_cam();
                cam_inst->set_world_to_cam(w2cam * scale * rotate);

                auto t0 = chrono::steady_clock::now();
                update_texture();
                auto t1 = chrono::steady_clock::now();

                std::cout << "Last frame rendered in: " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << "ms\n";
            }
        }
        sf::Sprite sprite(texture);
        window.clear();
        window.draw(sprite);
        window.display();
    }
}


