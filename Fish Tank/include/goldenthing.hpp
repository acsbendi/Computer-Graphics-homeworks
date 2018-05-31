//
// Created by Bendi on 5/30/2018.
//

#ifndef FISH_TANK_GOLDENTHING_HPP
#define FISH_TANK_GOLDENTHING_HPP

#include "intersectable.hpp"
#include "utils.hpp"

class GoldenThing : public Intersectable{
private:
    const vec3 center;
    const float radius;
    const vec3 coefficients;

public:
    GoldenThing(const vec3& _center, float _radius);

    Hit intersect(const Ray& ray) const override;
};


#endif //FISH_TANK_GOLDENTHING_HPP
