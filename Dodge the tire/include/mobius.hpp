//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_MOBIUS_HPP
#define DODGE_THE_TIRE_MOBIUS_HPP

#include "paramsurface.hpp"
#include "utils.hpp"

//---------------------------
class Mobius : public ParamSurface{
//---------------------------
private:
    const float R = 1;
    const float width;

public:
    Mobius(bool holes, float width);

    VertexData GenVertexData(float u, float v) const override;

    SurfacePointData GenSurfacePointData(float u, float v) const override;

};


#endif //DODGE_THE_TIRE_MOBIUS_HPP
