#include <cmath>
#include "vectors.h"

struct Vec3
{
	float x, y, z;
	Vec3() {}
	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
	Vec3 operator+(const Vec3 &v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
	Vec3 operator-(const Vec3 &v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
	Vec3 operator*(float d) const { return Vec3(x * d, y * d, z * d); }
	Vec3 operator/(float d) const { return Vec3(x / d, y / d, z / d); }
	Vec3 normalize() const
	{
		float mg = sqrt(x * x + y * y + z * z);
		return Vec3(x / mg, y / mg, z / mg);
	}
	float magSq() const
	{
		float mg = x * x + y * y + z * z;
		return mg;
	}
	float mag() const
	{
		float mg = x * x + y * y + z * z;
		return sqrt(mg);
	}
};

inline float dot(const Vec3 &a, const Vec3 &b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
inline Vec3 cross(const Vec3 &a, const Vec3 &b)
{
	return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
inline Vec3 elt_mult(const Vec3 &a, const Vec3 &b)
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