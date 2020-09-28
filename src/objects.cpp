#include "../headers/objects.h"

Vec3 objects::get_sphere_normal(objects::Sphere sphere, Vec3 pos)
{
	Vec3 N = pos - sphere.pos;
	return N.normalize();
}

Vec3 get_disc_normal(objects::Disc disc, Vec3 pos);
Vec3 get_plane_normal(objects::Plane plane, Vec3 pos);