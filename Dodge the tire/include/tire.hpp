//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_TIRE_HPP
#define DODGE_THE_TIRE_TIRE_HPP

#include "object.hpp"

class RaceTrack;

class Tire : public Object{
    static constexpr float R = 1, r = 0.5f, maxSpeed = 0.6f, acceleration = 0.01f;
    float speed = 0.06f;
    bool canAccelerate = false;

    const RaceTrack& raceTrack;

    const float uStart;
    float u;
    const unsigned int lane;
    mat4 rotationMatrix;
    float rollingAngle;
    vec3 rollingPivot;


public:
    Tire(shared_ptr<Shader> shader, const RaceTrack& raceTrack, unsigned lane, float uStart);

    void Animate(float tstart, float tend) override;

    mat4 GetM() const override;

    mat4 GetMinv() const override;

    void StartAcceleration();

    vec2 GetPositionOnTrack(float height) const;
};

#endif //DODGE_THE_TIRE_TIRE_HPP
