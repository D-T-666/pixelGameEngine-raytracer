#pragma once

#include <iostream>
#include <vector>
#include "./vectors.h"
#include "./objects.h"
#include "./camera.h"
#include "./ray.h"

class Scene
{

public:
	Scene();
	Scene(int _W, int _H);
	Scene(int _W, int _H, Camera _cam);

	void add_sphere(objects::Sphere obj);
	void add_disc(objects::Disc obj);
	void add_plane(objects::Plane obj);

	Vec3 trace_pixel(int x, int y);

	Ray _bounce_ray(Ray ray);
	Vec3 _shadow_ray(Vec3 pos);

private:
	std::vector<objects::Sphere> vspheres;
	std::vector<objects::Disc> vdiscs;
	std::vector<objects::Plane> vplanes;
	Camera cam;
	int WIDTH = 256;
	int HEIGHT = 256;
};