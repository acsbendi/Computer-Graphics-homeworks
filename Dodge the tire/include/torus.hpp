//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_TORUS_HPP
#define DODGE_THE_TIRE_TORUS_HPP

#include "paramsurface.hpp"

//---------------------------
class Torus : public ParamSurface {
//---------------------------
private:
    const float R, r;

    vec3 Point(float u, float v, float rr) const;
public:
    explicit Torus(float, float);

    VertexData GenVertexData(float u, float v) const override;
};

#endif //DODGE_THE_TIRE_TORUS_HPP
