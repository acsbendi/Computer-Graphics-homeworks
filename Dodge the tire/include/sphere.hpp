//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_SPHERE_HPP
#define DODGE_THE_TIRE_SPHERE_HPP

#include "paramsurface.hpp"

//---------------------------
class Sphere : public ParamSurface {
//---------------------------
public:
    Sphere();

    VertexData GenVertexData(float u, float v) const override;
};

#endif //DODGE_THE_TIRE_SPHERE_HPP
