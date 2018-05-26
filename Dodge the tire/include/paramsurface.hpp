//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_PARAMSURFACE_HPP
#define DODGE_THE_TIRE_PARAMSURFACE_HPP

#include "geometry.hpp"
#include "utils.hpp"

//---------------------------
class ParamSurface : public Geometry {
//---------------------------
protected:
    const bool holes;

public:
    explicit ParamSurface(bool holes);

    virtual VertexData GenVertexData(float u, float v) const = 0;

    virtual SurfacePointData GenSurfacePointData(float u, float v) const;

    void Create(int N = 16, int M = 16);
};

#endif //DODGE_THE_TIRE_PARAMSURFACE_HPP
