#include <cmath>
#include "../headers/vectors.h"

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

Vec3 clamp255(Vec3 &col)
{
	col = col * 255.0f;
	col.x = (col.x > 255.0f) ? 255.0f : (col.x < 0.0f) ? 0.0f : col.x;
	col.y = (col.y > 255.0f) ? 255.0f : (col.y < 0.0f) ? 0.0f : col.y;
	col.z = (col.z > 255.0f) ? 255.0f : (col.z < 0.0f) ? 0.0f : col.z;
	return col;
}

float randf()
{
	return float(rand()) / float((RAND_MAX));
}

Vec3 vabs(Vec3 vec)
{
	return Vec3(fabs(vec.x), fabs(vec.y), fabs(vec.z));
};