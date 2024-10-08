#pragma once

#include <cmath>

struct Vec3
{
  float x, y, z;
  Vec3() : x(0.0f), y(0.0f), z(0.0f) {}
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

float dot(const Vec3 &a, const Vec3 &b);
Vec3 vabs(Vec3 vec);
Vec3 cross(const Vec3 &a, const Vec3 &b);
Vec3 elt_mult(const Vec3 &a, const Vec3 &b);
Vec3 clamp255(Vec3 &col);
float randf();
