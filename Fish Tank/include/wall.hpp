//
// Created by Bendi on 5/30/2018.
//

#ifndef FISH_TANK_WALL_HPP
#define FISH_TANK_WALL_HPP

#include <memory>
#include "intersectable.hpp"
#include "utils.hpp"

using std::unique_ptr;

class Wall : public Intersectable{
    vec3 topLeftCorner, bottomLeftCorner, topRightCorner, bottomRightCorner;
    vec3 n1, n2;
    float NUMBER_OF_CELLS;

public:
    Wall(vec3 topLeftCorner, vec3 bottomLeftCorner, vec3 bottomRightCorner,
         unique_ptr<Material> material1, unique_ptr<Material> material2);

    Hit intersect(const Ray& ray) const override;
};


#endif //FISH_TANK_WALL_HPP
