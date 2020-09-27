#include "./scene.h"
#include <iostream>

Scene::Scene()
{
	std::cout << "int .cpp file\n";
}
Scene::Scene(int _W, int _H)
{
	WIDTH = _W;
	HEIGHT = _H;
}
Scene::Scene(int _W, int _H, Camera _cam)
{
	cam = _cam;
}

void Scene::add_sphere(objects::Sphere obj)
{
	vspheres.push_back(obj);
}
void Scene::add_disc(objects::Disc obj)
{
	vdiscs.push_back(obj);
}
void Scene::add_plane(objects::Plane obj)
{
	vplanes.push_back(obj);
}

Vec3 Scene::trace_pixel(int x, int y)
{
	// get the ray to trace
	float x_off = float(x) / float(WIDTH) * 2.0f - 1.0f;
	float y_off = float(y) / float(HEIGHT) * 2.0f - 1.0f;
	Ray ray = cam.get_ray(x_off, y_off);

	// bounce the ray n times
	// cast shadow rays on the way

	// return the color of the final ray
	return Vec3(x, y, 0);
};

Ray Scene::_bounce_ray(Ray ray)
{
	// TODO:
	// detect what the ray collides with.
	// calculate new ray color.
	// calculate the bounce ray.
	// return the bounce ray with the new collor.
	return Ray(Vec3(0, 0, 0), Vec3(0, 0, 1), Vec3(0, 0, 0));
}

Vec3 Scene::_shadow_ray(Vec3 pos)
{

	Ray ray;
	return Vec3(0, 0, 0);
}