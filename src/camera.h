#pragma once
#include "vectors.h"
#include "ray.h"

class Camera
{
private:
	Vec3 pos;
	Vec3 dir;
	float fov;

public:
	Camera() {}
	Camera(Vec3 _pos, Vec3 _dir) {}
	Ray get_ray(float x_offset, float y_offset) {}
};