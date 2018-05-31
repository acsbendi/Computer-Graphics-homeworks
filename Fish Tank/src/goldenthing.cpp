//
// Created by Bendi on 5/30/2018.
//

#include <memory>
#include "goldenthing.hpp"
#include "gold.hpp"
#include "hit.hpp"
#include "ray.hpp"

using std::make_unique;

GoldenThing::GoldenThing(const vec3 &center, float radius) :
        Intersectable{make_unique<Gold>()}, center{center}, radius{radius}, coefficients{3, 6, 4}
{}

Hit GoldenThing::intersect(const Ray &ray) const {
    Hit hit{};
    vec3 dist = ray.start - center;
    float a = dot(ray.dir, ray.dir * coefficients);
    float b = dot(dist, ray.dir * coefficients) * 2.0f;
    float c = dot(dist, dist * coefficients) - radius * radius;
    float discr = b * b - 4.0f * a * c;
    if (discr < 0) return hit;
    float sqrt_discr = sqrtf(discr);
    float t1 = (-b + sqrt_discr) / 2.0f / a;
    float t2 = (-b - sqrt_discr) / 2.0f / a;
    if (t1 <= 0 && t2 <= 0) return hit;
    if (t1 <= 0 && t2 > 0) hit.t = t2;
    else if (t2 <= 0 && t1 > 0) hit.t = t1;
    else if (t1 < t2) hit.t = t1;
    else hit.t = t2;
    hit.position = ray.start + ray.dir * hit.t;
    hit.normal = ((hit.position - center) * coefficients).normalize();
    hit.material = materials[0].get();
    return hit;
}
