//
// Created by Bendi on 5/31/2018.
//

#include "normalcamera.hpp"
#include "ray.hpp"

NormalCamera::NormalCamera(int endX, int endY, vec3 _eye, vec3 _lookat, vec3 vup, double fov,
                           vec3 sourceRefractiveIndex) : Camera(endX, endY, sourceRefractiveIndex) {
    eye = _eye;
    lookat = _lookat;
    vec3 w = eye - lookat;
    float f = w.length();
    right = cross(vup, w).normalize() * f * tan(fov / 2);
    up = cross(w, right).normalize() * f * tan(fov / 2);
}

Ray NormalCamera::getRay(int X, int Y) const {
    vec3 dir = lookat + right * (2.0 * (X + 0.5) / width - 1) + up * (2.0 * (Y + 0.5) / height - 1) - eye;
    return {eye, dir, false};
}
