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
}; // namespace objects