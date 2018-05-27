//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_CAMERA_HPP
#define DODGE_THE_TIRE_CAMERA_HPP

#include <memory>
#include "animatable.hpp"
#include "utils.hpp"
#include "collisiondetector.hpp"
#include "racetrack.hpp"

using std::unique_ptr;

class Animatable;

//---------------------------
class Camera : public Animatable { // 3D camera
//---------------------------
    vec3 wEye, wLookat, wVup;   // extinsic
    float fov, asp, fp, bp;       // intrinsic

    static constexpr float speed = -0.09f;
    static constexpr float distanceFromSurface = 0.2f;
    static constexpr unsigned int shakingEffectDuration = 40;
    static constexpr unsigned int shakingEffectStart = 20;

    unsigned int shakingEffectRemainingTime = 0;

    bool moving;
    unsigned int lane;
    float u;
    const RaceTrack& raceTrack;
    const unique_ptr<CollisionDetector const> collisionDetector;
    const unsigned int& windowWidth;
    const unsigned int& windowHeight;

public:
    Camera(const RaceTrack&, const vec3&, const vec3&,
           const vec3&, unique_ptr<CollisionDetector>&, const unsigned int&, const unsigned int&);

    mat4 V();

    mat4 P();

    const vec3 &GetWEye() const;

    void Animate(float tstart, float tend) override;

    void StartMoving();

    void SwitchLane(bool right);

    void OnResize();
};

#endif //DODGE_THE_TIRE_CAMERA_HPP
