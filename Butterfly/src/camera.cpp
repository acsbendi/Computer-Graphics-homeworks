//
// Created by Bendi on 5/27/2018.
//

#include "camera.hpp"

Camera::Camera() noexcept {
    Animate(0);
}

mat4 Camera::V() const { // view matrix: translates the center to the origin
    return {1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                -wCx, -wCy, 0, 1};
}

mat4 Camera::P() const { // projection matrix: scales it to be a square of edge length 2
    return {2 / wWx, 0, 0, 0,
                0, 2 / wWy, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1};
}

mat4 Camera::Vinv() const { // inverse view matrix
    return {1, 0, 0, 0,
                0, 1, 0, 0,
                0, 0, 1, 0,
                wCx, wCy, 0, 1};
}

mat4 Camera::Pinv() const { // inverse projection matrix
    return {wWx / 2, 0, 0, 0,
                0, wWy / 2, 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1};
}

void Camera::Animate(float) {
    wCx = 0; // 10 * cosf(t);
    wCy = 0;
    wWx = 10;
    wWy = 10;
}
