#include "../headers/scene.h"
#include <iostream>

Scene::Scene() {}
Scene::Scene(int _W, int _H)
{
	WIDTH = _W;
	HEIGHT = _H;
}
Scene::Scene(int _W, int _H, Camera _cam)
{
	WIDTH = _W;
	HEIGHT = _H;
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

Ray Scene::_bounce_ray(Ray ray, bool &shot_off)
{
	// TODO:
	// detect what the ray collides with.
	float min_d = 10000.0f;
	int is, id, ip;
	Vec3 hit_normal;
	Vec3 reflection_dir;
	Vec3 hit_pos;
	shot_off = true;
	for (int i = 0; i < vspheres.size(); i++)
	{
		float d = ray.intersect_sphere(vspheres[i]);
		if (d < min_d)
		{
			hit_pos = ray.pos + ray.dir * d;
			hit_normal = objects::get_sphere_normal(vspheres[i], hit_pos);
			reflection_dir = ray.dir + (hit_normal * 2 * dot(hit_normal, ray.dir));
			min_d = d;
			is = i;
			shot_off = false;
		}
	}
	// for (int i = 0; i < vdiscs.size(); i++)
	// {
	// 	float d = ray.intersect_disc(vdiscs[i]);
	// 	if (d < min_d)
	// 	{
	// 		min_d = d;
	// 		id = i;
	// 		shot_off = true;
	// 	}
	// }
	// for (int i = 0; i < vplanes.size(); i++)
	// {
	// 	float d = ray.intersect_plane(vplanes[i]);
	// 	if (d < min_d)
	// 	{
	// 		min_d = d;
	// 		ip = i;
	// 		shot_off = true;
	// 	}
	// }
	// calculate the collission point
	// calculate new ray color.
	// calculate the bounce ray.
	// return the bounce ray with the new collor.
	return Ray(hit_pos, reflection_dir, hit_normal);
}

Vec3 Scene::trace_pixel(int x, int y)
{
	// get the ray to trace
	float x_off = float(x) / float(WIDTH) * 2.0f - 1.0f;
	float y_off = float(y) / float(HEIGHT) * 2.0f - 1.0f;
	Ray ray = cam.get_ray(x_off, y_off);

	// bounce the ray n times
	bool shot_off = false; // to see if the ray shoots off into the distance
	int bounces = 1;
	while (!shot_off && bounces > 0)
	{
		ray = _bounce_ray(ray, shot_off);
		bounces--;
	}
	Vec3 col = ray.col;

	// cast shadow rays on the way

	// return the color of the final ray
	// return Vec3(shot_off ? x : 0, shot_off ? y : 0, 0);
	return Vec3(col.z * 255, col.z * 255, col.z * 255);
};

Vec3 Scene::_shadow_ray(Vec3 pos)
{

	Ray ray;
	return Vec3(0, 0, 0);
}