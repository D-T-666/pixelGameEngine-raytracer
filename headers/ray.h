#pragma once
#include "vectors.h"
#include "objects.h"

#include <vector>

struct RayIntersectionData
{
	Vec3 col = {1.0f, 1.0f, 1.0f};
	Vec3 light = {1.0f, 1.0f, 1.0f};
	float roughness = 0.0f;
	float specular = 1.0f;

	RayIntersectionData() {}
	RayIntersectionData(Vec3 c) : col(c) {}
	RayIntersectionData(Vec3 c, Vec3 l) : col(c), light(l) {}
	RayIntersectionData(Vec3 c, Vec3 l, float r) : col(c), light(l), roughness(r) {}
};

class Ray
{
public:
	Vec3 pos;
	Vec3 dir;
	std::vector<RayIntersectionData> hit_hist;

public:
	Ray(){};
	Ray(Vec3 _pos, Vec3 _dir) : pos(_pos), dir(_dir){};

	float intersect_sphere(objects::Sphere sph);
	float intersect_disc(objects::Disc disc);
	float intersect_plane(objects::Plane plane);

	Vec3 get_col();
};