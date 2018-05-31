//
// Created by Bendi on 5/30/2018.
//

#ifndef FISH_TANK_NORMALCAMERA_HPP
#define FISH_TANK_NORMALCAMERA_HPP

#include "camera.hpp"
#include "utils.hpp"

class NormalCamera : public Camera{
    vec3 eye, lookat, right, up;
public:
    NormalCamera(int endX, int endY, vec3 _eye, vec3 _lookat, vec3 vup, double fov,
                 vec3 sourceRefractiveIndex = vec3{1.0f,1.0f,1.0f});

    Ray getRay(int X, int Y) const override;
};


#endif //FISH_TANK_NORMALCAMERA_HPP
