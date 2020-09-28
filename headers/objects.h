#pragma once
#include "vectors.h"

namespace objects
{
	struct Sphere
	{
		Vec3 pos;
		float r;
		Vec3 col;
		Sphere(Vec3 p) : pos(p) {}
		Sphere(Vec3 p, float rad) : pos(p), r(rad) {}
		Sphere(Vec3 p, float rad, Vec3 c) : pos(p), r(rad), col(c) {}
	};

	struct Disc
	{
		Vec3 pos;
		Vec3 N;
		Vec3 col;
		Disc(Vec3 p) : pos(p) {}
		Disc(Vec3 p, Vec3 Normal) : pos(p), N(Normal) {}
		Disc(Vec3 p, Vec3 Normal, Vec3 c) : pos(p), N(Normal), col(c) {}
	};

	struct Plane
	{
		Vec3 abc;
		Vec3 col;
		Plane(Vec3 p) : abc(p) {}
		Plane(Vec3 p, Vec3 c) : abc(p), col(c) {}
	};

	Vec3 get_sphere_normal(Sphere sphere, Vec3 pos);
	Vec3 get_disc_normal(Disc disc, Vec3 pos);
	Vec3 get_plane_normal(Plane plane, Vec3 pos);
}; // namespace objects