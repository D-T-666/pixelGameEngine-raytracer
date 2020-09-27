#include "camera.h"
#include <cmath>

Camera::Camera()
{
	pos = {0.0f, 0.0f, 0.0f};
	dir = {1.0f, 0.0f, 0.0f};
	fov = 0.5 * PI;
};
Camera::Camera(Vec3 _pos, Vec3 _dir)
{
	pos = _pos;
	dir = _dir;
	fov = 0.5 * PI;
};
Camera::Camera(Vec3 _pos, Vec3 _dir, float fov)
{
	pos = _pos;
	dir = _dir;
	fov = fov;
};

Ray Camera::get_ray(float x_offset, float y_offset)
{
	Ray n_ray(pos, dir);
	return n_ray;
};