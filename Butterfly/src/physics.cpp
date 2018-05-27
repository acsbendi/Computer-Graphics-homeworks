//
// Created by Bendi on 5/27/2018.
//

#include "physics.hpp"

vec2 F(vec2 position, vec2 velocity){
    if((cursor - position).length() <= 0.01)
        return vec2(0,0);
    else return (cursor - position)*D - velocity * drag;
}

vec3 Fbut(vec2 position, float m){
    return vec3((cursor - position)*D) - vec3(0, 0, -9.81f)*m;
}
