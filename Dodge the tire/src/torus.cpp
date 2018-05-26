//
// Created by Bendi on 5/26/2018.
//

#include <cmath>
#include "utils.hpp"
#include "torus.hpp"

vec3 Torus::Point(float u, float v, float rr) const {
    float ur = u * 2.0f * static_cast<float >(M_PI), vr = v * 2.0f * static_cast<float >(M_PI);
    float l = R + rr * sinf(ur);
    return vec3(l * cosf(vr), l * sinf(vr), rr * cosf(ur));
}

Torus::Torus(const float R = 1, const float r = 0.5f) : ParamSurface(false), R(R), r(r) { Create(40, 40); }

VertexData Torus::GenVertexData(float u, float v) const {
    VertexData vd;
    vd.position = Point(u, v, r);
    vd.normal = (vd.position - Point(u, v, 0)) * (1.0f / r);
    vd.texcoord = vec2(u, v);
    return vd;
}