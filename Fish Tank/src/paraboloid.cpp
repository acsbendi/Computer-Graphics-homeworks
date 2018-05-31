//
// Created by Bendi on 5/31/2018.
//

#include <memory>
#include <iostream>
#include "paraboloid.hpp"
#include "hit.hpp"
#include "ray.hpp"
#include "material.hpp"

using std::move;

Paraboloid::Paraboloid(const vec3 &center, unique_ptr<Material> material) : Intersectable{move(material)},
                                                                              center{center}
{}

Hit Paraboloid::intersect(const Ray &ray) const {
    Hit hit{};
    float a = ray.dir.x * ray.dir.x + ray.dir.z * ray.dir.z;
    float b = 2.0f * (ray.start.x * ray.dir.x + ray.start.z * ray.dir.z - ray.dir.x * center.x - ray.dir.z * center.z -
                      ray.dir.y);
    float c = ray.start.x * ray.start.x + center.x * center.x - 2.0f * center.x * ray.start.x +
              ray.start.z * ray.start.z + center.z * center.z - 2.0f * center.z * ray.start.z - ray.start.y + center.y;
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
    vec3 normal1 = (vec3(-2.0f * (hit.position.x - center.x), 1, -2.0f * (hit.position.z - center.z))).normalize();
    vec3 normal2 = (vec3(2.0f * (hit.position.x - center.x), 1, 2.0f * (hit.position.z - center.z))).normalize();
    hit.normal = dot(normal1, ray.dir) < 0 ? normal1 : normal2;
    hit.material = materials[0].get();
    return hit;
}
