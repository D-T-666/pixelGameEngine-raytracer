#include "../headers/ray.h"

float Ray::intersect_sphere(objects::Sphere sph)
{
    const double p = dot(sph.pos - pos, dir);
    const double y = (pos + dir * p - sph.pos).magSq();
    const double len = sqrt(sph.r * sph.r - y);
    const double t0 = p - len;
    const double t1 = p + len;
    return ((t0 < t1 && t0 > 0) ? t0 : t1);
}

// float Ray::intersect_disc(objects::Disc disc)
// {
//     const float denom = dot(ray.d, n);
//     if (denom > 1e-6)
//     {
//         const Vec3 p0l0 = n * p0 - ray.o;
//         const double t = dot(p0l0, n) / denom;
//         const Vec3 poi = ray.d * t + ray.o;
//         return t;
//     }
//     return -1.0;
// }

// float Ray::intersect_plane(objects::Plane plane)
// {
//     const float denom = dot(ray.d, plane.N);
//     if (denom > 1e-6)
//     {
//         const Vec3 p0l0 = plane.N * plane.pos - pos;
//         const double t = dot(p0l0, n) / denom;
//         const Vec3 poi = dir * t + pos;
//         return t;
//     }
//     return -1.0;
// }