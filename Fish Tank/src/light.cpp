//
// Created by Bendi on 5/31/2018.
//

#include "light.hpp"

Light::Light(vec3 position, vec3 Le) : position{position}, Le{Le} {}

vec3 Light::getLe(vec3 point) {
    return Le / (position - point).length() / (position - point).length();
}

vec3 Light::getPosition() const {
    return position;
}