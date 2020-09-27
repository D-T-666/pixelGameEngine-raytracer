#pragma once
#include "vectors.h"

class Ray
{
private:
	Vec3 pos;
	Vec3 dir;
	Vec3 col;

public:
	Ray(){};
	Ray(Vec3 _pos, Vec3 _dir) : pos(_pos), dir(_dir){};
	Ray(Vec3 _pos, Vec3 _dir, Vec3 _col) : pos(_pos), dir(_dir), col(_col){};
};