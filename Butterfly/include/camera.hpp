//
// Created by Bendi on 5/27/2018.
//

#ifndef BUTTERFLY_CAMERA_HPP
#define BUTTERFLY_CAMERA_HPP

#include "utils.hpp"

// 2D camera
struct Camera {
    float wCx, wCy;	// center in world coordinates
    float wWx, wWy;	// width and height in world coordinates
public:
    Camera() noexcept ;

    mat4 V() const;

    mat4 P() const;

    mat4 Vinv() const;

    mat4 Pinv() const;

    void Animate(float t);
};

extern Camera camera;

#endif //BUTTERFLY_CAMERA_HPP
