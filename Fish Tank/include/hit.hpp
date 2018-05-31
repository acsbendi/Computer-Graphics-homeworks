//
// Created by Bendi on 5/30/2018.
//

#ifndef FISH_TANK_HIT_HPP
#define FISH_TANK_HIT_HPP

#include "utils.hpp"

class Material;

struct Hit {
    float t = -1;
    vec3 position{};
    vec3 normal{};
    Material * material = nullptr;
};

#endif //FISH_TANK_HIT_HPP
