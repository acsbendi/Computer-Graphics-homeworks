//
// Created by Bendi on 5/26/2018.
//

#include "utils.hpp"
#include "sphere.hpp"

Sphere::Sphere() : ParamSurface(false) { Create(50, 50); }

VertexData Sphere::GenVertexData(float u, float v) const {
    VertexData vd;
    vd.position = vd.normal = vec3(cosf(u * 2.0f * static_cast<float>(M_PI)) * sinf(v * static_cast<float>(M_PI)),
                                   sinf(u * 2.0f * static_cast<float>(M_PI)) * sinf(v * static_cast<float>(M_PI)),
                                   cosf(v * static_cast<float>(M_PI)));
    vd.texcoord = vec2(u, v);
    return vd;
}
