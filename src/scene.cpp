
#include "scene.h"
#include <iostream>

Scene::Scene() {}
Scene::Scene(Camera _cam)
{
	cam = _cam;
}

void Scene::_add_shpere(objects::Sphere obj)
{
	spheres.push_back(obj);
}