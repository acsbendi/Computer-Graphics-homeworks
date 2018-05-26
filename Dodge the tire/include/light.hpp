//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_LIGHT_HPP
#define DODGE_THE_TIRE_LIGHT_HPP

#include "animatable.hpp"

//---------------------------
class Light : public Animatable{
//---------------------------
public:
    vec3 La, Le;
    vec4 wLightPos;

    void Animate(float tstart, float tend) override {    }
};

#endif //DODGE_THE_TIRE_LIGHT_HPP
