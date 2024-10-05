#pragma once
#include "vectors.h"
#include "constants.h"
#include "ray.h"

class MyCamera
{
public:
	Vec3 pos;
	Vec3 dir;
	float fov = 0.1f;
	float fnear = 0.1f;

public:
	MyCamera();
	MyCamera(Vec3 _pos, Vec3 _dir);
	MyCamera(Vec3 _pos, Vec3 _dir, float fov);
	MyRay get_ray(float x_offset, float y_offset);
};
