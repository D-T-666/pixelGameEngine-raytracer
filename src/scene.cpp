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

void Scene::add_plight(lights::Point light)
{
	vplights.push_back(light);
}

bool Scene::_shadow_ray(Ray ray)
{
	for (int i = 0; i < vspheres.size(); i++)
	{
		if (ray.intersect_sphere(vspheres[i]) > 0.0f)
		{
			return false;
		}
	}
	return true;
}

Ray Scene::_bounce_ray(Ray ray, bool &shot_off)
{
	float min_d = 10000.0f;
	Vec3 hit_normal;
	Vec3 reflection_dir;
	Vec3 hit_pos;
	RayIntersectionData intersection_data;
	shot_off = true;
	for (int i = 0; i < vspheres.size(); i++)
	{
		float d = ray.intersect_sphere(vspheres[i]);
		if (d > 0.0f && d < min_d)
		{
			// Calculate the reflection direction
			hit_pos = ray.pos + ray.dir * d;
			hit_normal = objects::get_sphere_normal(vspheres[i], hit_pos);
			reflection_dir = ray.dir - (hit_normal * 2.0f * dot(hit_normal, ray.dir));

			// save the intersection data
			intersection_data.col = vspheres[i].mat.col;
			intersection_data.roughness = vspheres[i].mat.roughness;

			// get the light information
			if (1)
			{
				const lights::Point light = vplights[0];
				const Vec3 to_light = light.pos - hit_pos;
				const Ray light_ray = Ray(hit_pos, to_light.normalize());
				const float ambient_light = 0.1f;
				if (_shadow_ray(light_ray))
				{
					const float dp = dot(hit_normal.normalize(), to_light.normalize());
					const float intensity = fmax(fmin(1.0f / to_light.magSq(), 1.0f), ambient_light);
					intersection_data.light = light.col * (dp > ambient_light ? dp : ambient_light); // * intensity;
				}
				else
				{
					intersection_data.light = {ambient_light, ambient_light, ambient_light};
				}
				intersection_data.specular = pow(fmax(dot(to_light.normalize(), reflection_dir.normalize()), 0.0f), 50);
			}

			min_d = d;
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

	if (shot_off)
	{
		intersection_data.col = {0.0f, 0.0f, 0.0f};
		intersection_data.light = {0.0f, 0.0f, 0.0f};
		intersection_data.roughness = 1.0f;
		intersection_data.specular = 0.0f;
	}

	ray.pos = hit_pos;
	ray.dir = reflection_dir.normalize();
	ray.hit_hist.push_back(intersection_data);
	return ray;
	// return Ray(hit_pos, reflection_dir.normalize(), intersection_data);
}

Vec3 Scene::trace_pixel(int x, int y)
{
	// get the ray to trace
	float x_off = float(x) / float(WIDTH) * 2.0f - 1.0f;
	float y_off = float(y) / float(HEIGHT) * 2.0f - 1.0f;
	Ray ray = cam.get_ray(x_off, y_off);
	Vec3 col;

	// bounce the ray n times
	bool shot_off = false; // to see if the ray shoots off into the distance
	ray = _bounce_ray(ray, shot_off);
	if (!shot_off)
	{
		int bounces = 5;
		while (!shot_off && bounces > 0)
		{
			ray = _bounce_ray(ray, shot_off);
			bounces--;
		}

		col = ray.get_col();

		// col = Vec3(1.0f, 1.0f, 1.0f);
	}

	return Vec3(col.x * 255, col.y * 255, col.z * 255);
};