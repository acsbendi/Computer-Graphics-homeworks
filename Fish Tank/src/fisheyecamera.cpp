//
// Created by Bendi on 5/31/2018.
//

#include "fisheyecamera.hpp"
#include "ray.hpp"

FishEyeCamera::FishEyeCamera(int endX, int endY, vec3 eye, vec3 sourceRefractiveIndex) :
        Camera(endX, endY, sourceRefractiveIndex), eye{eye}
{}

Ray FishEyeCamera::getRay(int x, int y) const {
    float alpha = 2 * static_cast<float>(M_PI) * (static_cast<float>(x) / width + 0.25f);
    float beta = (static_cast<float>(M_PI) * (static_cast<float>(y) / height - 0.5f));
    vec3 dir = vec3(cosf(alpha) * cosf(beta), sinf(beta), sinf(alpha) * cosf(beta));
    return {eye, dir, false};
}