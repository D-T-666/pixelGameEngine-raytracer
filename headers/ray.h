#pragma once
#include "vectors.h"
#include "objects.h"

class Ray
{
public:
	Vec3 pos;
	Vec3 dir;
	Vec3 col;

public:
	Ray(){};
	Ray(Vec3 _pos, Vec3 _dir) : pos(_pos), dir(_dir){};
	Ray(Vec3 _pos, Vec3 _dir, Vec3 _col) : pos(_pos), dir(_dir), col(_col){};

	float intersect_sphere(objects::Sphere sph);
	float intersect_disc(objects::Disc disc);
	float intersect_plane(objects::Plane plane);
};