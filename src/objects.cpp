#include "../headers/objects.h"

Vec3 objects::get_sphere_normal(objects::Sphere sphere, Vec3 pos)
{
	Vec3 N = pos - sphere.pos;
	return N.normalize();
}

Vec3 get_disc_normal(objects::Disc disc, Vec3 pos);
Vec3 objects::get_plane_normal(Plane plane, Vec3 pos)
{
	Vec3 N = plane.pos.normalize() * -1.0f;
	// if (dot(N, pos - plane.pos) < 0.0f)
	// 	N = N * -1.0f;
	return N;
};