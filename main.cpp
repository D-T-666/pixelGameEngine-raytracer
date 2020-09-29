#define OLC_PGE_APPLICATION
#include "headers/olcPixelGameEngine.h"
#include "headers/scene.h"

class RayTracer : public olc::PixelGameEngine
{
public:
	RayTracer()
	{
		sAppName = "Ray-Tracer";
	}

private:
	Scene my_scene;

public:
	bool OnUserCreate() override
	{
		Camera cam(Vec3(0.0f, 0.0f, -4.0f), Vec3(0.0f, 0.0f, 1.0f));
		my_scene = Scene(256, 256, cam);

		objects::Sphere n_sphere_d(Vec3(-1.f, 1.0f, 0.0f), 0.65f, Material(Vec3(0.1f, 0.1f, 1.0f), 0.5f));
		objects::Sphere n_sphere_u(Vec3(-1.f, -1.f, 0.0f), 0.65f, Material(Vec3(1.0f, 0.1f, 0.1f), 0.5f));
		objects::Sphere n_sphere_l(Vec3(1.0f, 1.0f, 0.0f), 0.35f, Material(Vec3(0.1f, 1.0f, 0.1f), 0.5f));
		objects::Sphere n_sphere_m(Vec3(1.0f, -1.f, 0.0f), 0.15f, Material(Vec3(1.0f, 1.0f, 1.0f), 0.05f));
		my_scene.add_sphere(n_sphere_d);
		my_scene.add_sphere(n_sphere_u);
		my_scene.add_sphere(n_sphere_l);
		my_scene.add_sphere(n_sphere_m);

		lights::Point n_plight(Vec3(2.75f, 2.25f, 0.0f), Vec3(1.0f, 1.0f, 1.0f), 1.0f);
		my_scene.add_plight(n_plight);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		for (int x = 0; x < ScreenWidth(); x++)
		{
			for (int y = 0; y < ScreenHeight(); y++)
			{
				Vec3 col = my_scene.trace_pixel(x, y);
				Draw(x, y, olc::Pixel(col.x, col.y, col.z));
			}
		}

		float x = my_scene.cam.pos.x;
		float y = my_scene.cam.pos.y;
		float z = my_scene.cam.pos.z;
		const float theta = 0.02f;
		my_scene.cam.pos = {x * cos(theta) + z * sin(theta),
							y,
							x * -sin(theta) + z * cos(theta)};
		x = my_scene.cam.pos.x;
		y = my_scene.cam.pos.y;
		z = my_scene.cam.pos.z;
		my_scene.cam.dir = {-x, -y, -z};
		my_scene.cam.dir = my_scene.cam.dir.normalize();
		return true;
	}
};

int main()
{
	RayTracer App;
	if (App.Construct(256, 256, 1, 1))
		App.Start();
	return 0;
}