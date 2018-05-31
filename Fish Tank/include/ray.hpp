//
// Created by Bendi on 5/30/2018.
//

#ifndef FISH_TANK_RAY_HPP
#define FISH_TANK_RAY_HPP

#include "utils.hpp"

struct Ray {
    vec3 start, dir;
    bool out;

    Ray(vec3 start, vec3 dir, bool out);
};


#endif //FISH_TANK_RAY_HPP
