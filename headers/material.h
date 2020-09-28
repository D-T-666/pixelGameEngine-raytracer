#pragma once

#include "vectors.h"

struct Material
{
    Vec3 col = {1.0f, 1.0f, 1.0f};
    float roughness = 1.0f;
    Material(){};
    Material(Vec3 c) : col(c) {}
    Material(Vec3 c, float r) : col(c), roughness(r) {}
};