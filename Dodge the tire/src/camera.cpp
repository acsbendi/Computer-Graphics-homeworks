//
// Created by Bendi on 5/26/2018.
//

#include <memory>
#include "collisiondetector.hpp"
#include "racetrack.hpp"
#include "camera.hpp"
#include "utils.hpp"

using std::unique_ptr;
using std::move;

Camera::Camera(const RaceTrack& raceTrack, const vec3& wEye, const vec3& wLookat,
       const vec3& wVup, unique_ptr<CollisionDetector>& collisionDetector, const unsigned int& windowWidth, const unsigned int& windowHeight)
        : raceTrack(raceTrack), wEye(wEye), wLookat(wLookat), wVup(wVup), collisionDetector(move(collisionDetector)),
          windowWidth(windowWidth), windowHeight(windowHeight){
    asp = 1;
    fov = 60.0f * (float)M_PI / 180.0f;
    fp = 0.1; bp = 10;
    moving = false;
    lane = 0;
    u = 0;
}

mat4 Camera::V() { // view matrix: translates the center to the origin
    vec3 w = (wEye - wLookat).normalize();
    vec3 u = vec3::cross(wVup, w).normalize();
    vec3 v = vec3::cross(w, u);
    return mat4::TranslateMatrix(-wEye) * mat4(u.x, v.x, w.x, 0,
                                         u.y, v.y, w.y, 0,
                                         u.z, v.z, w.z, 0,
                                         0,   0,   0,   1);
}

mat4 Camera::P() { // projection matrix
    return mat4(1 / (tanf(fov / 2)*asp), 0, 0, 0,
                0, 1 / tanf(fov / 2), 0, 0,
                0, 0, -(fp + bp) / (bp - fp), -1,
                0, 0, -2 * fp*bp / (bp - fp), 0);
}

const vec3& Camera::GetWEye() const {
    return wEye;
}

void Camera::Animate(float tstart, float tend) {
    if(moving){
        u += speed*(tend-tstart);
        if(u < 0.0f){
            u += 2.0f;
        }

        SurfacePointData spd = raceTrack.GetData(u,lane);

        if(shakingEffectDuration - shakingEffectRemainingTime > shakingEffectStart &&
           collisionDetector->CheckCollision(lane, u)){
            shakingEffectRemainingTime = shakingEffectDuration;
        }

        if(shakingEffectRemainingTime > 0) {
            vec3 shakingVector = spd.normal * (shakingEffectRemainingTime % 2 == 0 ? 0.1f : -0.1f)
                                 + spd.tangentV * (shakingEffectRemainingTime % 2 == 0 ? 0.1f : -0.1f);

            wEye = spd.position + spd.normal * distanceFromSurface + shakingVector;

            shakingEffectRemainingTime--;
        }
        else
            wEye = spd.position + spd.normal * distanceFromSurface;
        wLookat = wEye + spd.tangentU * speed;
        wVup = spd.normal;
    }
}

void Camera::StartMoving(){
    moving = true;
    fov = 90.0f * (float)M_PI / 180.0f;
}

void Camera::SwitchLane(bool right){
    if(right and lane < raceTrack.GetNumberOfLanes() - 1)
        lane++;
    else if(!right && lane > 0)
        lane--;
}

void Camera::OnResize(){
    asp = windowWidth/windowHeight;
}