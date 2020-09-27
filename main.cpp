#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "src/vectors.h"
#include "src/objects.h"

//

//

//

class Scene
{
private:
	std::vector<objects::Sphere> spheres;

public:
	Scene()
	{
	}

	void _add_shpere(objects::Sphere obj)
	{
		spheres.push_back(obj);
	}
};

//

//

class Example : public olc::PixelGameEngine
{
public:
	Example()
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
	Example demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();
	return 0;
}