#pragma once
#include "vectors.h"
#include "constants.h"
#include "ray.h"

class Camera
{
public:
	Vec3 pos;
	Vec3 dir;
	float fov = 0.1f;
	float fnear = 0.1f;

public:
	Camera();
	Camera(Vec3 _pos, Vec3 _dir);
	Camera(Vec3 _pos, Vec3 _dir, float fov);
	Ray get_ray(float x_offset, float y_offset);
};