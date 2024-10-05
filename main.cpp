#include "headers/scene.h"
#include <fstream>
#include "headers/raylib.h"

class MyRayTracer {
public:
  MyRayTracer() {}

private:
  Scene my_scene;
  int frameCount = 0;
  float fps_sum = 0.0f;

  std::ofstream out;

public:
  bool OnUserCreate() {
    MyCamera cam(Vec3(0.0f, 0.0f, -4.0f), Vec3(0.0f, 0.0f, 1.0f));
    my_scene = Scene(Width, Height, cam);

    objects::Sphere n_sphere_d(Vec3(-1.f, 0.35f, -1.f), 0.65f,
                               Mat(Vec3(0.1f, 0.1f, 1.0f), 0.9f));
    objects::Sphere n_sphere_u(Vec3(-1.f, 0.35f, 1.0f), 0.65f,
                               Mat(Vec3(1.0f, 0.1f, 0.1f), 0.5f));
    objects::Sphere n_sphere_l(Vec3(1.0f, 0.65f, -1.f), 0.35f,
                               Mat(Vec3(0.1f, 1.0f, 0.1f), 0.3f));
    objects::Sphere n_sphere_m(Vec3(1.0f, 0.05f, 1.0f), 0.95f,
                               Mat(Vec3(1.0f, 1.0f, 0.0f), 0.1f));
    my_scene.add_sphere(n_sphere_d);
    my_scene.add_sphere(n_sphere_u);
    my_scene.add_sphere(n_sphere_l);
    my_scene.add_sphere(n_sphere_m);

    objects::Plane n_plane_a(Vec3(0.0f, 1.0f, 0.0f),
                             Mat(Vec3(1.0f, 1.0f, 1.0f), 0.6f));
    my_scene.add_plane(n_plane_a);

    lights::Point n_plight_a(Vec3(1.0f, -1.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f),
                             5.0f);
    lights::Point n_plight_b(Vec3(-1.f, -1.0f, 0.0f), Vec3(1.0f, 1.0f, 1.0f),
                             5.0f);
    my_scene.add_plight(n_plight_a);
    my_scene.add_plight(n_plight_b);
    out = std::ofstream("out.ppm");
    out << "P3\n" << Width << ' ' << Height << ' ' << "155\n";
    return true;
  }

  bool OnUserUpdate(float fElapsedTime) {
    for (int y = 0; y < GetScreenHeight(); y++) {
      for (int x = 0; x < GetScreenWidth(); x++) {
        Vec3 col = my_scene.trace_pixel(x, y);

        if (frameCount == 0) {
          out << (int)col.x << ' ' << (int)col.y << ' ' << (int)col.z << '\n';
        }
        DrawPixel(x, y,
            Color{(unsigned char)((int)col.x), (unsigned char)((int)col.y),
                (unsigned char)((int)col.z), (unsigned char)255});
      }
    }

    float x = my_scene.cam.pos.x;
    float y = my_scene.cam.pos.y;
    float z = my_scene.cam.pos.z;
    const float theta = 0.02f;
    my_scene.cam.pos = Vec3(x * cos(theta) + z * sin(theta),
    						y,
    						x * -sin(theta) + z * cos(theta)); //
    // *1.002f;
    // my_scene.cam.pos.y -= 0.01f;
    x = my_scene.cam.pos.x;
    y = my_scene.cam.pos.y;
    z = my_scene.cam.pos.z;
    my_scene.cam.dir = {-x, -y, -z};
    my_scene.cam.dir = my_scene.cam.dir.normalize();
    fps_sum += fElapsedTime;
    frameCount++;
    if (frameCount % 250 == 0) {
      std::cout << frameCount << " "
                << 1.0f / (float(fps_sum) / float(frameCount)) << "\n";
      frameCount = 0;
      fps_sum = 0.0f;
    }
    return true;
  }
};

int main() {
  MyRayTracer App;

  InitWindow(Width, Height, "Raytracer");

  App.OnUserCreate();

  while (!WindowShouldClose()) {
    BeginDrawing();
    App.OnUserUpdate(GetFrameTime());
    EndDrawing();
  }

  // if (App.Construct(Width, Height, 1, 1))
  // 	App.Start();
  return 0;
}
