#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "src/scene.h"

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
		objects::Sphere n_shpere(Vec3(1.0f, 1.0f, 1.0f), 1.0f);
		my_scene._add_shpere(n_shpere);
		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		for (int x = 0; x < ScreenWidth(); x++)
			for (int y = 0; y < ScreenHeight(); y++)
				Draw(x, y, olc::Pixel(rand() % 256, rand() % 256, rand() % 256));
		return true;
	}
};

int main()
{
	RayTracer App;
	if (App.Construct(256, 240, 4, 4))
		App.Start();
	return 0;
}