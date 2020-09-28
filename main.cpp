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
		Camera cam(Vec3(0.0f, 0.0f, -5.0f), Vec3(0.0f, 0.0f, 1.0f));
		my_scene = Scene(256, 256, cam);

		objects::Sphere n_shpere_mid(Vec3(0.0f, 1.0f, 0.0f), 0.5f);
		objects::Sphere n_shpere_up(Vec3(0.0f, -1.0f, 0.0f), 0.5f);
		my_scene.add_sphere(n_shpere_up);
		my_scene.add_sphere(n_shpere_mid);
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
		return true;
	}
};

int main()
{
	RayTracer App;
	if (App.Construct(256, 256, 2, 2))
		App.Start();
	return 0;
}