#pragma once
#include "vectors.h"
#include "objects.h"

#include <vector>

struct MyRayIntersectionData
{
	Vec3 col = Vec3(1.0f, 1.0f, 1.0f);
	Vec3 light = Vec3(1.0f, 1.0f, 1.0f);
	float roughness = 0.0f;
	float specular = 0.0f;

	MyRayIntersectionData() {}
	MyRayIntersectionData(Vec3 c) : col(c) {}
	MyRayIntersectionData(Vec3 c, Vec3 l) : col(c), light(l) {}
	MyRayIntersectionData(Vec3 c, Vec3 l, float r) : col(c), light(l), roughness(r) {}
};

class MyRay
{
public:
	Vec3 pos;
	Vec3 dir;
	std::vector<MyRayIntersectionData> hit_hist;

public:
	MyRay(){};
	MyRay(Vec3 _pos, Vec3 _dir) : pos(_pos), dir(_dir){};

	float intersect_sphere(objects::Sphere sph);
	float intersect_disc(objects::Disc disc);
	float intersect_plane(objects::Plane plane);

	bool intersects_sphere(objects::Sphere sph);

	Vec3 get_col();
};
