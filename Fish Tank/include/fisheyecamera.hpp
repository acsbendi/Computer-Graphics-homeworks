//
// Created by Bendi on 5/30/2018.
//

#ifndef FISH_TANK_FISHEYECAMERA_HPP
#define FISH_TANK_FISHEYECAMERA_HPP

#include "camera.hpp"

class FishEyeCamera : public Camera {
    vec3 eye;
public:
    explicit FishEyeCamera(int endX, int endY,
                           vec3 eye = vec3{0.0f,0.0f,0.0f}, vec3 sourceRefractiveIndex = vec3{1.0f,1.0f,1.0f});

    Ray getRay(int x, int y) const override;
};


#endif //FISH_TANK_FISHEYECAMERA_HPP
