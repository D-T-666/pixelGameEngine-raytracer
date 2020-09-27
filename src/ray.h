#pragma once
#include "vectors.h"

class Ray
{
private:
	Vec3 pos;
	Vec3 dir;

public:
	Ray(){};
	Ray(Vec3 _pos, Vec3 _dir) : pos(_pos), dir(_dir){};
};