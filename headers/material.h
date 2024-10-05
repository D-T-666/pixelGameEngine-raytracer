#pragma once

#include "vectors.h"

struct Mat
{
    Vec3 col = Vec3(1.0f, 1.0f, 1.0f);
    float roughness = 1.0f;
    float specular = 0.0f;
    Mat(){};
    Mat(Vec3 c) : col(c) {}
    Mat(Vec3 c, float r) : col(c), roughness(r) {}
    Mat(Vec3 c, float r, float s) : col(c), roughness(r), specular(s) {}
};
