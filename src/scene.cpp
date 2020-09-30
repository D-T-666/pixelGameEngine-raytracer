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
		if (ray.intersects_sphere(vspheres[i]))
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
	for (unsigned int i = 0; i < vspheres.size(); i++)
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

			// deal with stuff
			min_d = d;
			shot_off = false;
		}
	}
	for (unsigned int i = 0; i < vplanes.size(); i++)
	{
		float d = ray.intersect_plane(vplanes[i]);
		if (d > 0.0f && d < min_d)
		{
			// Calculate the reflection direction
			hit_pos = ray.pos + ray.dir * d;
			hit_normal = objects::get_plane_normal(vplanes[i], hit_pos);
			reflection_dir = ray.dir - (hit_normal * 2.0f * dot(hit_normal, ray.dir));

			// save the intersection data
			intersection_data.col = vplanes[i].mat.col * (int(hit_pos.x - 100) % 2 ^ int(hit_pos.z - 100) % 2 ? 1.0f : 0.4f);
			intersection_data.roughness = vplanes[i].mat.roughness;

			// deal with stuff
			min_d = d;
			shot_off = false;
		}
	}

	if (shot_off)
	{
		intersection_data.col = {1.0f, 1.0f, 1.0f};
		intersection_data.light = {fAmbient_light, fAmbient_light, fAmbient_light};
		intersection_data.roughness = 1.0f;
		intersection_data.specular = 0.0f;
	}
	else if (!shot_off)
	{
		reflection_dir = reflection_dir.normalize();

		intersection_data.light = {fAmbient_light, fAmbient_light, fAmbient_light};

		for (int i = 0; i < vplights.size(); i++)
		{
			const lights::Point light = vplights[i];
			Vec3 to_light = light.pos - hit_pos;
			const float d2light = to_light.magSq();
			to_light = to_light / sqrt(d2light);

			if (_shadow_ray(Ray(hit_pos, to_light)))
			{
				float dp = dot(hit_normal, to_light);
				float intensity = fmin(1.0f / d2light, 1.0f);

				intersection_data.light = intersection_data.light + elt_mult(light.col, (Vec3(1.0f, 1.0f, 1.0f) - intersection_data.light) * fmax((dp > fAmbient_light ? dp : fAmbient_light) * intensity, fAmbient_light));
				intersection_data.specular += pow(fmax(dot(to_light, reflection_dir), 0.0f), 50);
			}
		}
	}

	ray.pos = hit_pos;
	ray.dir = reflection_dir;
	ray.hit_hist.push_back(intersection_data);
	return ray;
	// return Ray(hit_pos, reflection_dir.normalize(), intersection_data);
}

Vec3 Scene::trace_pixel(int x, int y)
{
	// get the ray to trace
	Ray ray = cam.get_ray(float(x) / float(WIDTH) * 2.0f - 1.0f,
						  float(y) / float(HEIGHT) * 2.0f - 1.0f);

	// bounce the ray n times
	bool shot_off = false; // to see if the ray shoots off into the distance
	int bounces = 100;
	while (!shot_off && bounces > 0)
	{
		ray = _bounce_ray(ray, shot_off);
		bounces--;
	}

	Vec3 col = ray.get_col();

	return clamp255(col);
}