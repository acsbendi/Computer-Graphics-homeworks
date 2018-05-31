//
// Created by Bendi on 5/30/2018.
//

#ifndef FISH_TANK_PARABOLOID_HPP
#define FISH_TANK_PARABOLOID_HPP

#include <memory>
#include "intersectable.hpp"
#include "utils.hpp"

using std::unique_ptr;
using std::move;

class Paraboloid : public virtual Intersectable {
    vec3 center;

public:
    Paraboloid(const vec3& center, unique_ptr<Material> material);

    Hit intersect(const Ray& ray) const override ;
};


#endif //FISH_TANK_PARABOLOID_HPP
