//
// Created by Bendi on 5/30/2018.
//

#ifndef FISH_TANK_LIGHT_HPP
#define FISH_TANK_LIGHT_HPP

#include "utils.hpp"

class Light {
private:
    vec3 position;
    vec3 Le;
public:
    Light(vec3 position, vec3 Le);

    vec3 getLe(vec3 point);

    vec3 getPosition() const;
};


#endif //FISH_TANK_LIGHT_HPP
