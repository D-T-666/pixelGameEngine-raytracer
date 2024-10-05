#pragma once

#include <iostream>
#include <vector>
#include "./vectors.h"
#include "./objects.h"
#include "./lights.h"
#include "./camera.h"
#include "./ray.h"
#include "./constants.h"

class Scene
{

public:
	Scene();
	Scene(int _W, int _H);
	Scene(int _W, int _H, MyCamera _cam);

	void add_sphere(objects::Sphere obj);
	void add_disc(objects::Disc obj);
	void add_plane(objects::Plane obj);

	void add_plight(lights::Point light);

	Vec3 trace_pixel(int x, int y);

	MyRay _bounce_ray(MyRay ray, bool &shot_off);
	bool _shadow_ray(MyRay ray);

private:
	std::vector<objects::Sphere> vspheres;
	std::vector<objects::Disc> vdiscs;
	std::vector<objects::Plane> vplanes;

	std::vector<lights::Point> vplights; // vector of point lights

public:
	MyCamera cam;
	int WIDTH = 256;
	int HEIGHT = 256;
};
