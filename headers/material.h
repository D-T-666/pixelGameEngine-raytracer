#pragma once

#include "vectors.h"

struct Material
{
    Vec3 col = {1.0f, 1.0f, 1.0f};
    float roughness = 1.0f;
    float specular = 0.0f;
    Material(){};
    Material(Vec3 c) : col(c) {}
    Material(Vec3 c, float r) : col(c), roughness(r) {}
    Material(Vec3 c, float r, float s) : col(c), roughness(r), specular(s) {}
};