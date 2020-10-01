#define OLC_PGE_APPLICATION
#include "headers/olcPixelGameEngine.h"
#include "headers/scene.h"
#include <fstream>

class RayTracer : public olc::PixelGameEngine
{
public:
	RayTracer()
	{
		sAppName = "Ray-Tracer";
	}

private:
	Scene my_scene;
	int frameCount = 0;
	float fps_sum = 0.0f;

	std::ofstream out;

public:
	bool OnUserCreate() override
	{
		Camera cam(Vec3(0.0f, 0.0f, -4.0f), Vec3(0.0f, 0.0f, 1.0f));
		my_scene = Scene(Width, Height, cam);

		objects::Sphere n_sphere_d(Vec3(-1.f, 0.35f, -1.f), 0.65f, Material(Vec3(0.1f, 0.1f, 1.0f), 0.9f));
		objects::Sphere n_sphere_u(Vec3(-1.f, 0.35f, 1.0f), 0.65f, Material(Vec3(1.0f, 0.1f, 0.1f), 0.5f));
		objects::Sphere n_sphere_l(Vec3(1.0f, 0.65f, -1.f), 0.35f, Material(Vec3(0.1f, 1.0f, 0.1f), 0.3f));
		objects::Sphere n_sphere_m(Vec3(1.0f, 0.05f, 1.0f), 0.95f, Material(Vec3(1.0f, 1.0f, 0.0f), 0.1f));
		my_scene.add_sphere(n_sphere_d);
		my_scene.add_sphere(n_sphere_u);
		my_scene.add_sphere(n_sphere_l);
		my_scene.add_sphere(n_sphere_m);
		for (int x = -3; x <= 3; x++)
		{
			for (int z = -3; z <= 3; z++)
			{
				objects::Sphere n_sphere(Vec3(x, 0.85f, z), 0.15f, Material(Vec3(1.0f, 1.0f, 1.0f), 0.0f));
				my_scene.add_sphere(n_sphere);
			}
		}

		objects::Plane n_plane_a(Vec3(0.0f, 1.0f, 0.0f), Material(Vec3(1.0f, 1.0f, 1.0f), 0.6f));
		my_scene.add_plane(n_plane_a);

		lights::Point n_plight_a(Vec3(1.0f, -1.0f, 0.0f), Vec3(1.0f, 0.8f, 0.0f), 5.0f);
		lights::Point n_plight_b(Vec3(-1.f, -1.0f, 0.0f), Vec3(0.0f, 0.8f, 1.0f), 5.0f);
		my_scene.add_plight(n_plight_a);
		my_scene.add_plight(n_plight_b);
		out = std::ofstream("out.ppm");
		out << "P3\n"
			<< Width << ' ' << Height << ' ' << "155\n";
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		for (int y = 0; y < ScreenHeight(); y++)
		{
			for (int x = 0; x < ScreenWidth(); x++)
			{
				Vec3 col = my_scene.trace_pixel(x, y);

				if (frameCount == 0)
				{
					out << (int)col.x << ' '
						<< (int)col.y << ' '
						<< (int)col.z << '\n';
				}
				Draw(x, y, olc::Pixel(col.x, col.y, col.z));
			}
		}

		// float x = my_scene.cam.pos.x;
		// float y = my_scene.cam.pos.y;
		// float z = my_scene.cam.pos.z;
		// const float theta = 0.02f;
		// my_scene.cam.pos = Vec3(x * cos(theta) + z * sin(theta),
		// 						y,
		// 						x * -sin(theta) + z * cos(theta)); // *1.002f;
		// // my_scene.cam.pos.y -= 0.01f;
		// x = my_scene.cam.pos.x;
		// y = my_scene.cam.pos.y;
		// z = my_scene.cam.pos.z;
		// my_scene.cam.dir = {-x, -y, -z};
		// my_scene.cam.dir = my_scene.cam.dir.normalize();
		fps_sum += fElapsedTime;
		frameCount++;
		if (frameCount % 250 == 0)
		{
			std::cout << frameCount << " " << 1.0f / (float(fps_sum) / float(frameCount)) << "\n";
			frameCount = 0;
			fps_sum = 0.0f;
		}
		return true;
	}
};

int main()
{
	RayTracer App;
	if (App.Construct(Width, Height, 1, 1))
		App.Start();
	return 0;
}