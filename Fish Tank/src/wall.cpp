//
// Created by Bendi on 5/30/2018.
//

#include <memory>
#include "wall.hpp"
#include "hit.hpp"
#include "ray.hpp"
#include "material.hpp"

using std::move;

Wall::Wall(vec3 topLeftCorner, vec3 bottomLeftCorner, vec3 bottomRightCorner,
           unique_ptr<Material> material1, unique_ptr<Material> material2) :
        topLeftCorner(topLeftCorner), bottomLeftCorner(bottomLeftCorner), bottomRightCorner(bottomRightCorner)
{
    topRightCorner = topLeftCorner + (bottomRightCorner - bottomLeftCorner);
    n1 = cross(bottomLeftCorner - topLeftCorner, bottomRightCorner - bottomLeftCorner).normalize();
    n2 = cross(bottomRightCorner - bottomLeftCorner, bottomLeftCorner - topLeftCorner).normalize();

    materials.push_back(move(material1));
    materials.push_back(move(material2));

    NUMBER_OF_CELLS = 10;
}

Hit Wall::intersect(const Ray &ray) const {
    Hit hit{};
    float t = dot(topLeftCorner - ray.start, n1) / dot(ray.dir, n1);
    vec3 p = ray.start + ray.dir * t;
    vec3 local = p - topLeftCorner;
    vec3 X = topRightCorner - topLeftCorner;
    vec3 Y = bottomLeftCorner - topLeftCorner;
    float x = local.length() * dot(X.normalize(), local.normalize());
    float y = local.length() * dot(Y.normalize(), local.normalize());

    if (x < 0 || y < 0 || x > X.length() || y > Y.length())
        return hit;
    hit.position = p;
    hit.t = t;
    if (dot(ray.dir, n1) < 0)
        hit.normal = n1;
    else
        hit.normal = n2;

    float d;
    float xCellSize = X.length() / NUMBER_OF_CELLS;
    float xInCell = modff(x / xCellSize, &d);
    float yCellSize = Y.length() / NUMBER_OF_CELLS;
    float yInCell = modff(y / yCellSize, &d);
    if (xInCell + yInCell < 1)
        hit.material = materials[0].get();
    else
        hit.material = materials[1].get();

    return hit;
}
