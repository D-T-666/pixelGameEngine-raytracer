#include <fstream>
#include <cmath>
#include <iostream>

// -- helper functions and structs --

struct Vec3
{
	double x, y, z;
	Vec3(double x, double y, double z) : x(x), y(y), z(z) {}
	Vec3 operator+(const Vec3 &v) const { return Vec3(x + v.x, y + v.y, z + v.z); }
	Vec3 operator-(const Vec3 &v) const { return Vec3(x - v.x, y - v.y, z - v.z); }
	Vec3 operator*(double d) const { return Vec3(x * d, y * d, z * d); }
	Vec3 operator/(double d) const { return Vec3(x / d, y / d, z / d); }
	Vec3 normalize() const
	{
		double mg = sqrt(x * x + y * y + z * z);
		return Vec3(x / mg, y / mg, z / mg);
	}
	double magSq() const
	{
		double mg = x * x + y * y + z * z;
		return mg;
	}
	double mag() const
	{
		double mg = x * x + y * y + z * z;
		return sqrt(mg);
	}
};
inline double dot(const Vec3 &a, const Vec3 &b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}
inline Vec3 cross(const Vec3 &a, const Vec3 &b)
{
	return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
inline Vec3 elt_mult(const Vec3 &a, const Vec3 &b)
{
	return Vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}
void clamp255(Vec3 &col)
{
	col = col * 255;
	col.x = (col.x > 255) ? 255 : (col.x < 0) ? 0 : col.x;
	col.y = (col.y > 255) ? 255 : (col.y < 0) ? 0 : col.y;
	col.z = (col.z > 255) ? 255 : (col.z < 0) ? 0 : col.z;
}
double randf()
{
	return float(rand()) / float((RAND_MAX));
}

// -- rays --
struct Ray
{
	Vec3 o, d, c;
	Ray(Vec3 _o, Vec3 _d, Vec3 _c) : o(_o), d(_d), c(_c) {}
};

// -- objects and object functions --

double get_sphere_intersection(const Vec3 &c, const double &r, const Ray &ray)
{
	const double p = dot(c - ray.o, ray.d);
	const double y = (ray.o + ray.d * p - c).magSq();
	const double len = sqrt(r * r - y);
	const double t0 = p - len;
	const double t1 = p + len;
	return ((t0 < t1 && t0 > 0) ? t0 : t1);
}

bool intersects_sphere(const Vec3 &c, const double &r, const Ray &ray)
{
	const double p = dot(c - ray.o, ray.d);
	const double y = (ray.o + ray.d * p - c).magSq();
	return (p > 0) ? y < r * r : false;
}

double get_plane_intersection(const Vec3 &n, const double &p0, const Ray &ray)
{
	const float denom = dot(ray.d, n);
	if (denom > 1e-6)
	{
		const Vec3 p0l0 = n * p0 - ray.o;
		const double t = dot(p0l0, n) / denom;
		const Vec3 poi = ray.d * t + ray.o;
		return t;
	}
	return -1.0;
}

struct Obj
{
	Vec3 p;
	double a;
	Vec3 col;
	double reflectivity;
	double clarity;
	int type;

	Obj() : p(Vec3(0, 0, 0)), a(1.0), col(Vec3(1, 1, 1)), reflectivity(1.0), clarity(1.0), type(0) {}
	Obj(Vec3 p, double a, Vec3 col, double ref, double cla, int type) : p(p), a(a), col(col), reflectivity(ref), clarity(cla), type(type) {}

	Vec3 get_normal(Vec3 to) const
	{
		switch (type)
		{
		case 0:
			return Vec3(to - p).normalize();
		case 1:
			return (dot(p, to - p * a) > 0) ? p : p * -1;
		}
	}

	bool intersects(Ray &ray) const
	{
		switch (type)
		{
		case 0:
			return intersects_sphere(p, a, ray);
		case 1:
			return get_plane_intersection(p, a, ray) > 0;
		}
	}

	double get_intersection(Ray &ray) const
	{
		switch (type)
		{
		case 0:
			return get_sphere_intersection(p, a, ray);
		case 1:
			return get_plane_intersection(p, a, ray);
		}
	}
};
struct Light
{
	Vec3 p;
	double intensity;
	double r = 0.1;
	Vec3 c;

	Light() : p(Vec3(0, 0, 0)), c(Vec3(1, 1, 1)), intensity(1.0){};
	Light(Vec3 p, Vec3 c, double intensity) : p(p), c(c), intensity(intensity){};

	bool intersects(Ray &ray) const
	{
		return get_sphere_intersection(p, r, ray) != 0;
	}

	double get_intersection(Ray &ray) const
	{
		return get_sphere_intersection(p, r, ray);
	}
};
struct Camera
{
	Vec3 p;
	Vec3 n;
	double d;
	Camera(Vec3 p, Vec3 n, double d) : p(p), n(n), d(d) {}

	Ray get_ray(double x, double y)
	{
		Vec3 o = p - n * d;
		Vec3 d = cross(Vec3(0, 1, 0), n) * x + cross(cross(Vec3(0, 1, 0), n), n) * -y + n;
		return Ray(o, (d).normalize(), Vec3(1, 1, 1));
	}
};

// -- main functions --
bool cast(Ray &ray, Obj *objects, Light *lights, double &t_final, bool &object_or_light_final, Obj &object_hit_final, Light &light_hit_final)
{
	Obj object_hit;
	Light light_hit;
	bool hit = false;
	bool object_or_light = false;
	double min_t = 10000000.0;
	for (unsigned int i = 0; i < 5; i++)
	{
		// std::cout << i;
		if (objects[i].intersects(ray))
		{
			const double t = objects[i].get_intersection(ray);
			if (t > 0 && t < min_t)
			{
				min_t = t;
				object_hit = objects[i];
				hit = true;
			}
		}
	}
	for (unsigned int i = 0; i < 2; i++)
	{
		// std::cout << i;
		if (lights[i].intersects(ray))
		{
			const double t = lights[i].get_intersection(ray);
			if (t > 0 && t < min_t)
			{
				min_t = t;
				light_hit = lights[i];
				hit = true;
				object_or_light = true;
			}
		}
	}
	if (hit)
	{
		if (object_or_light)
		{
			light_hit_final = light_hit;
			t_final = min_t;
			object_or_light_final = true;
		}
		else
		{
			t_final = min_t;
			object_hit_final = object_hit;
			object_or_light_final = false;
		}
	}
	else
	{
		t_final = 0;
	}
	return hit;
}

bool cast_shadow(Ray &ray, Obj *objects)
{
	for (int i = 0; i < 5; i++)
	{
		if (intersects_sphere(objects[i].p, objects[i].a, ray))
		{
			return true;
		}
	}
	return false;
}

void trace(Ray &ray, Obj *objects, Light *lights, int max_bounces, int bounces)
{
	double t = 0;
	Obj object_hit;
	bool object_or_light = false;
	Light light_hit;
	if (bounces < max_bounces && cast(ray, objects, lights, t, object_or_light, object_hit, light_hit))
	{
		if (!object_or_light)
		{
			const Vec3 poi = ray.o + ray.d * t;
			const Vec3 N = object_hit.get_normal(poi);

			Vec3 new_dir = ray.d + (N * 2 * -dot(N, ray.d));

			Vec3 new_col = elt_mult(ray.c, object_hit.col);

			if (object_hit.clarity == 1.0)
			{
				Ray new_ray(poi, new_dir, new_col);
				trace(new_ray, objects, lights, max_bounces, bounces + 1);
				ray.c = new_ray.c;
			}
			else
			{
				float r = randf();
				Vec3 dir = Vec3(randf() * 2 - 1, randf() * 2 - 1, randf() * 2 - 1);
				while (dot(dir, N) < 0)
				{
					dir = Vec3(randf() * 2 - 1, randf() * 2 - 1, randf() * 2 - 1);
				}
				Ray new_ray(poi, (new_dir + (dir * (1 - object_hit.clarity))).normalize(), new_col);
				trace(new_ray, objects, lights, max_bounces, bounces + 1);
				new_ray.c;
				ray.c = elt_mult(ray.c, new_ray.c) * object_hit.clarity; // * object_hit.clarity + object_hit.col * (1 - object_hit.clarity);
			}
		}
		else
		{
			ray.c = light_hit.c;
		}
	}
	else if (bounces > 0)
	{

		const Vec3 poi = ray.o + ray.d * t;

		// add light and shadow rays and calculate the color of the final bounce
		Vec3 col(1, 1, 1);

		for (int i = 0; i < 2; i++)
		{
			Ray shadow_ray(poi, (lights[i].p + Vec3(randf() * 2 - 1, randf() * 2 - 1, randf() * 2 - 1).normalize() * lights[i].r - poi).normalize(), Vec3(1, 1, 1));
			if (!cast_shadow(shadow_ray, objects))
			{
				col = col + elt_mult(object_hit.col, lights[i].c * (lights[i].intensity / (lights[i].p - poi).magSq()));
			}
		}
		col = col / (2 + 1);
		ray.c = elt_mult(ray.c, col);
	}
	else
	{
		ray.c = Vec3(0.8, 0.8, 0.8);
	}
}

//  -----------
int main()
{
	// -- constants --
	const int H = 2048;
	const int W = H;
	const int sample_count = 100;
	const int sample_x = sqrt(sample_count);
	const int sample_y = sqrt(sample_count);

	// -- creating a file --
	std::ofstream out("out.ppm");
	out << "P3\n"
		<< W << ' ' << H << ' ' << "255\n";

	// -- objects --
	Obj objects[5] = {
		Obj(Vec3(0.0, 1.0, 0.0), 0.0, Vec3(0.5, 0.5, 0.5), 1.0, 0.8, 1),
		Obj(Vec3(-.1, -.25, 2.5), 0.25, Vec3(1.0, 1.0, 1.0), 1.0, 1.0, 0),
		Obj(Vec3(0.55, -.30, 2.), 0.30, Vec3(1.0, 0.0, 1.0), 1.0, 0.8, 0),
		Obj(Vec3(-.52, -.27, 1.8), 0.27, Vec3(0.0, 1.0, 1.0), 1.0, 0.95, 0),
		Obj(Vec3(0.1, -.15, 1.2), 0.15, Vec3(1.0, 0.8, 0.0), 1.0, 0.5, 0)};
	Light lights[2] = {
		Light(Vec3(-1., -1., 0.5), Vec3(1, 1, 1), 1.0),
		Light(Vec3(1.0, -1., 0.5), Vec3(1, 1, 1), 1.0)};
	Camera camera(Vec3(0, -0.25, 1.25), Vec3(0, 0.25, 1).normalize(), 0.5);

	// -- looping over every pixel and storing it in the file --
	for (int y = 0; y < H; ++y)
	{
		for (int x = 0; x < W; ++x)
		{
			Vec3 pix_col = Vec3(0, 0, 0);
			for (float sub_y = 0.0f; sub_y < 1.0f; sub_y += 1 / double(sample_x))
			{
				for (float sub_x = 0.0f; sub_x < 1.0f; sub_x += 1 / double(sample_y))
				{
					Ray ray = camera.get_ray(
						float(x + sub_x) / float(W) * 2 - 1,
						float(y + sub_y) / float(H) * 2 - 1);
					// Ray ray(
					// 	Vec3(0, 0, 0),
					// 	Vec3((float(x) + sub_x) / double(W) * 2 - 1, (float(y) + sub_y) / double(H) * 2 - 1, 1).normalize(),
					// 	Vec3(1, 1, 1));

					trace(ray, objects, lights, 8, 0);

					pix_col = pix_col + ray.c;
				}
			}
			pix_col = pix_col / double(sample_count);
			clamp255(pix_col);
			out << (int)pix_col.x << ' '
				<< (int)pix_col.y << ' '
				<< (int)pix_col.z << '\n';
		}
		std::cout << y << "\n";
	}
}