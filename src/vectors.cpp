#include <cmath>
#include "vectors.h"

//

//

float dot(const Vec3 &a, const Vec3 &b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

Vec3 cross(const Vec3 &a, const Vec3 &b)
{
	return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

Vec3 elt_mult(const Vec3 &a, const Vec3 &b)
{
	return Vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

void clamp255(Vec3 &col)
{
	col = col * 255;
	col.x = (col.x > 255) ? 255 : (col.x < 0) ? 0 : col.x;
	col.y = (col.y > 255) ? 255 : (col.y < 0) ? 0 : col.y;
	col.z = (col.z > 255) ? 255 : (col.z < 0) ? 0 : col.z;
}

float randf()
{
	return float(rand()) / float((RAND_MAX));
}