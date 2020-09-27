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
	// get the direction of the ray
	Vec3 right_dir = cross(Vec3(0, 1, 0), dir);
	Vec3 up_dir = cross(right_dir, dir);
	Vec3 ray_dir = right_dir *  x_offset + 
					  up_dir * -y_offset +
					  	 dir;
						   
	// get the origin of the ray
	Vec3 ray_pos = pos + ray_dir * fnear;

	// return a newly constructed ray with new origin and a direction
	return Ray(ray_pos, ray_dir.normalize(), Vec3(1, 1, 1));
};