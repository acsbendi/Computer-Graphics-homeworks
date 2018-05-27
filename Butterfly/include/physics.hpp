//
// Created by Bendi on 5/27/2018.
//

#ifndef BUTTERFLY_PHYSICS_HPP
#define BUTTERFLY_PHYSICS_HPP

#include "utils.hpp"
#include "cursor.hpp"

constexpr float drag = 0.6f;
constexpr float D = 0.3f;

vec2 F(vec2 position, vec2 velocity);

vec3 Fbut(vec2 position, float m);

#endif //BUTTERFLY_PHYSICS_HPP
