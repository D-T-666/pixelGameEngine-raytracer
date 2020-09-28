#include "../headers/ray.h"

float Ray::intersect_sphere(objects::Sphere sph)
{

    const float p = dot(sph.pos - pos, dir);
    const float y = (pos + dir * p - sph.pos).magSq();
    if ((p > 0) ? y < sph.r * sph.r : false)
    {
        const float l = sqrt((sph.r * sph.r) - y);
        const float t0 = p - l;
        const float t1 = p + l;
        return ((t0 < t1 && t0 > 0.0f) ? t0 : t1);
    }
    return -1.0f;
}

// float Ray::intersect_disc(objects::Disc disc)
// {
//     const float denom = dot(ray.d, n);
//     if (denom > 1e-6)
//     {
//         const Vec3 p0l0 = n * p0 - ray.o;
//         const float t = dot(p0l0, n) / denom;
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
//         const float t = dot(p0l0, n) / denom;
//         const Vec3 poi = dir * t + pos;
//         return t;
//     }
//     return -1.0;
// }