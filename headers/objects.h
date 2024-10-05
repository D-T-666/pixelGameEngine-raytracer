#pragma once
#include "vectors.h"
#include "material.h"

namespace objects
{
	struct Sphere
	{
		Vec3 pos;
		float r;
		Mat mat;
		Sphere(Vec3 p) : pos(p) {}
		Sphere(Vec3 p, float rad) : pos(p), r(rad) {}
		Sphere(Vec3 p, float rad, Mat m) : pos(p), r(rad), mat(m) {}
	};

	struct Disc
	{
		Vec3 pos;
		Vec3 N;
		Mat mat;
		Disc(Vec3 p) : pos(p) {}
		Disc(Vec3 p, Vec3 Normal) : pos(p), N(Normal) {}
		Disc(Vec3 p, Vec3 Normal, Mat m) : pos(p), N(Normal), mat(m) {}
	};

	struct Plane
	{
		Vec3 pos;
		Mat mat;
		Plane(Vec3 p) : pos(p) {}
		Plane(Vec3 p, Mat m) : pos(p), mat(m) {}
	};

	Vec3 get_sphere_normal(Sphere sphere, Vec3 pos);
	Vec3 get_disc_normal(Disc disc, Vec3 pos);
	Vec3 get_plane_normal(Plane plane, Vec3 pos);
}; // namespace objects
