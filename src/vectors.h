#pragma once

const float PI = 3.14159265358979323846264338;

struct Vec3
{
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;
  Vec3() {}
  Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
  Vec3 operator+(const Vec3 &v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
  Vec3 operator-(const Vec3 &v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
  Vec3 operator*(float d) const { return Vec3(x * d, y * d, z * d); }
  Vec3 operator/(float d) const { return Vec3(x / d, y / d, z / d); }
};
inline float dot(const Vec3 &a, const Vec3 &b);
inline Vec3 cross(const Vec3 &a, const Vec3 &b);
inline Vec3 elt_mult(const Vec3 &a, const Vec3 &b);
void clamp255(Vec3 &col);
float randf();