//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_RENDERSTATE_HPP
#define DODGE_THE_TIRE_RENDERSTATE_HPP

#include "utils.hpp"

class Material;
class Light;
class Texture;

//---------------------------
struct RenderState {
//---------------------------
    mat4     MVP, M, Minv, V, P;
    Material* material;
    Light*     light;
    Texture*  texture;
    vec3     wEye;
};

#endif //DODGE_THE_TIRE_RENDERSTATE_HPP
