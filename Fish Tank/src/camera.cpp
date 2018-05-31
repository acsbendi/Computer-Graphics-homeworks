//
// Created by Bendi on 5/30/2018.
//

#include "camera.hpp"

Camera::Camera(int width, int height, const vec3& sourceRefractiveIndex) :
        width(width), height(height), sourceRefractiveIndex(sourceRefractiveIndex)
{}

void Camera::set(int width, int height){
    this->width = width;
    this->height = height;
}
const vec3& Camera::getSourceRefractiveIndex() const {
    return sourceRefractiveIndex;
}

Camera::~Camera() = default;