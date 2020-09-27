#pragma once

#include "vectors.h"
#include "objects.h"
#include "camera.h"
#include "ray.h"
#include <iostream>

class Scene
{
private:
	std::vector<objects::Sphere> spheres;
	Camera cam;
	int WIDTH;
	int HEIGHT;

public:
	Scene();
	Scene(Camera _cam);

	void _add_shpere(objects::Sphere obj);

	void _trace_pixel(int x, int y);
};