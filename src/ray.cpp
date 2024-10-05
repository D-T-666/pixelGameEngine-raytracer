#include "../headers/ray.h"

float MyRay::intersect_sphere(objects::Sphere sph)
{

    const float p = dot(sph.pos - pos, dir);
    const float y = (pos + dir * p - sph.pos).magSq();
    const float r_sq = sph.r * sph.r;
    if ((p > 0) ? y < r_sq : false)
    {
        const float l = sqrt(r_sq - y);
        return ((-l < l && p - l > 0.0f) ? p - l : p + l);
    }
    return -1.0f;
}

bool MyRay::intersects_sphere(objects::Sphere sph)
{
    const float p = dot(sph.pos - pos, dir);
    const float y = (pos + dir * p - sph.pos).magSq();
    return (p > 0) ? y < sph.r * sph.r : false;
}

Vec3 MyRay::get_col()
{
    Vec3 col = {1.0f,
                1.0f,
                1.0f};

    while (hit_hist.size() > 0)
    {
        MyRayIntersectionData data = hit_hist.back();

        Vec3 hit_col = elt_mult(data.col, data.light) + Vec3(1.0f, 1.0f, 1.0f) * (data.specular * (1.0f - data.roughness));
        col = col * (1.0f - data.roughness) + hit_col * data.roughness;

        hit_hist.pop_back();
    }

    return col;
}

// float MyRay::intersect_disc(objects::Disc disc)
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

float MyRay::intersect_plane(objects::Plane plane)
{
    // assuming vectors are all normalized
    float denom = dot(plane.pos.normalize(), dir);
    if (denom > 1e-6)
    {
        Vec3 p0l0 = plane.pos - pos;
        float t = dot(p0l0, plane.pos.normalize()) / denom;
        if (t >= 0.0f)
            return t;
    }
    return -1.0f;
}
