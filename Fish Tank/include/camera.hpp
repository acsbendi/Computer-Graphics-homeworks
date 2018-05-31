//
// Created by Bendi on 5/30/2018.
//

#ifndef FISH_TANK_CAMERA_HPP
#define FISH_TANK_CAMERA_HPP

#include "utils.hpp"

struct Ray;

class Camera{
protected:
    int width, height;
    vec3 sourceRefractiveIndex;

protected:
    Camera(int width, int height, const vec3& sourceRefractiveIndex);

public:
    void set(int width, int height);

    const vec3 &getSourceRefractiveIndex() const;

    virtual Ray getRay(int X, int Y) const = 0;

    virtual ~Camera();
};

#endif //FISH_TANK_CAMERA_HPP
