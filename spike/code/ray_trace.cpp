#include <chrono>
#include <iostream>
#include <vector>

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
//    { 0.707107f, -0.331295f, 0.624695f, 0.f,
//            0.f,  0.883452f, 0.468521f, 0.f,
//     -0.707107f, -0.331295f, 0.624695f, 0.f,
//      -1.53871f, -5.747777f, -40.400412f, 1.f });

alpha::math::Matrix44f world2cam(
    { 1.0000f, 0.0000f, 0.0000f, 0.0000f,
    0.0000f, 1.0000f, 0.0000f, 0.0000f,
    0.0000f, 0.0000f, 1.0000f, 0.0000f,
    0.0000f, 0.0000f, 0.0000f, 1.0000f, }
);


auto cam = make_shared<Camera>(width, height, aperture_width, aperture_height, z_near, z_far, focal_length,
        world2cam);


int main() {
	alpha::Scene scene;
	auto obptr = make_shared<Circle>(0.f, 0.f, 0.25f);
	obptr->color = { 255, 140, 71};

	scene.emplace_back(obptr);

	alpha::Tracer raytracer(cam);
	auto t0 = chrono::steady_clock::now();
	raytracer.trace(scene);
	auto t1 = chrono::steady_clock::now();

	cout << "Time taken: " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count()
		<< "ms" << endl;
    raytracer.dump_as_ppm("trace.ppm");
}
