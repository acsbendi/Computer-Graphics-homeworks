//
// Created by Bendi on 5/26/2018.
//

#include "mobius.hpp"
#include "utils.hpp"

Mobius::Mobius(bool holes, float width) : ParamSurface(holes), width(width) { Create(40, 40); }

VertexData Mobius::GenVertexData(float u, float v) const {
    VertexData vd;

    SurfacePointData spd = GenSurfacePointData(u, v);

    vd.position = spd.position;
    vd.normal = spd.normal;

    vd.texcoord = vec2(u, v);

    return vd;
}

SurfacePointData Mobius::GenSurfacePointData(float u, float v) const {
    SurfacePointData spd;

    float U = u * static_cast<float >(M_PI), V = (v - 0.5f) * width;
    float C2U = cosf(2 * U), S2U = sinf(2 * U);
    float D = R + V * cosf(U), dDdU = -V * sinf(U), dDdV = cosf(U);
    spd.position = vec3(D * C2U, D * S2U, V * sinf(U));

    vec3 drdU(dDdU * C2U - D * S2U * 2, dDdU * S2U + D * C2U * 2,
              V * cosf(U));
    vec3 drdV(dDdV * C2U, dDdV * S2U, sinf(U));

    spd.tangentU = drdU;
    spd.tangentV = drdV;
    spd.normal = vec3::cross(drdU, drdV);

    return spd;
}