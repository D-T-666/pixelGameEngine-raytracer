#pragma once

#include "vectors.h"

namespace lights
{
    struct Point
    {
        Vec3 pos;
        Vec3 col{1.0f, 1.0f, 1.0f};
        float intensity = 1.0f;
        float radius = 1.0f;
        Point() {}
        Point(Vec3 _pos) : pos(_pos) {}
        Point(Vec3 _pos, Vec3 _col) : pos(_pos), col(_col) {}
        Point(Vec3 _pos, Vec3 _col, float _intensity) : pos(_pos), col(_col), intensity(_intensity) {}
    };
}; // namespace lights