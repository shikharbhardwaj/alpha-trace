#include <chrono>
#include <iostream>
#include <vector>
#include <random>

#include <alpha/buffers.hpp>
#include <alpha/camera.hpp>
#include <alpha/math.hpp>
#include <alpha/objects.hpp>
#include <alpha/trace.hpp>

using namespace alpha::buffers;
using namespace alpha::math;
using namespace alpha::objects;
using namespace alpha;
using namespace std;

const int width = 1920, height = 1080;
const float aperture_width = 0.980f, aperture_height = 0.735f, focal_length = 20, z_near = 1, z_far = 1000;

//alpha::math::Matrix44f world2cam(
//	{
//	 0.945519f,		  0.f, -0.325569f, 0.f,
//	-0.179534f, 0.834209f, -0.521403f, 0.f,
//	 0.271593f, 0.551447f,  0.788760f, 0.f,
//	 4.208271f, 8.374532f, 17.932925f, 1.f
//	});
//alpha::math::Matrix44f world2cam(
//    { 0.707107f, -0.331295f, 0.624695f, 0.f,
//            0.f,  0.883452f, 0.468521f, 0.f,
//     -0.707107f, -0.331295f, 0.624695f, 0.f,
//      -1.53871f, -5.747777f, -40.400412f, 1.f });

alpha::math::Matrix44f world2cam(
    {
	1.0000f, 0.0000f, 0.0000f, 0.0000f,
    0.0000f, 1.0000f, 0.0000f, 0.0000f,
    0.0000f, 0.0000f, 1.0000f, 0.0000f,
    0.0000f, 0.0000f, 0.0000f, 1.0000f, }
);

//alpha::math::Matrix44f world2cam(
//	{
//	0.7071f,  0.0000f, -0.7071f,  0.0000f,
//	0.0000f,  1.0000f,  0.0000f,  0.0000f,
//	0.7071f,  0.0000f,  0.7071f,  0.0000f,
//	0.0000f,  0.0000f,  0.0000f,  1.0000f,
//});
//alpha::math::Matrix44f world2cam(
//	{
//		0.7071f,  0.3536f, -0.6123f, 0.0000f,
//		0.0000f,  0.8660f,  0.5000f, 0.0000f,
//		0.7071f, -0.3536f,  0.6123f, 0.0000f,
//		0.0000f,  0.0000f,  0.0000f, 1.0000f
//	});

auto cam = make_shared<Camera>(width, height, aperture_width, aperture_height, z_near, z_far, focal_length,
        world2cam);


int main() {
	std::random_device rd;
	std::mt19937 gen(rd());
	gen.seed(0);

	std::uniform_real_distribution<float> dist;
	std::uniform_int_distribution<int> cdist(0, 255);

	alpha::Scene scene;

	// Set up a good scene.
	//auto bg_plane = make_shared<Plane>(Vec3f(0.f, 0.f, -1.f), Vec3f(0.f, 0.f, -100.f));
	//bg_plane->color = {135, 206, 235};
	//scene.push_back(bg_plane);

	const int num_spheres = 32;
	for (int i = 0; i < num_spheres; i++) {
		Vec3f pos((0.5f - dist(gen)) * 15.f, (0.5f - dist(gen)) * 15.f, (0.5f + dist(gen) * -10.f));
		float r = (0.5f + dist(gen) * 0.5f);
		auto sp = make_shared<Sphere>(pos, r);
		sp->color = { (uint8_t)cdist(gen), (uint8_t)cdist(gen), (uint8_t)cdist(gen) };

		scene.push_back(sp);
	}

	//auto disk = make_shared<Disk>(Vec3f(0.f, 0.f, -1.f), Vec3f(0.f, 0.f, -5.f), 0.5f);
	//disk->color = { (uint8_t)cdist(gen), (uint8_t)cdist(gen), (uint8_t)cdist(gen) };
	//scene.push_back(disk);

	auto box = make_shared<AABB>(Vec3f(0.f, 0.f, -7.f), Vec3f(0.5f, 0.5f, -3.f));
	box->color = { (uint8_t)cdist(gen), (uint8_t)cdist(gen), (uint8_t)cdist(gen) };
	scene.push_back(box);

	alpha::Tracer raytracer(cam);
	auto t0 = chrono::steady_clock::now();
	raytracer.trace(scene);
	auto t1 = chrono::steady_clock::now();

	cout << "Time taken: " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count()
		<< "ms" << endl;
    raytracer.dump_as_ppm("trace.ppm");
}
