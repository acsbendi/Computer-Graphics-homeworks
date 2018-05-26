//
// Created by Bendi on 5/26/2018.
//

#include <memory>
#include "racetrack.hpp"
#include "collisiondetector.hpp"
#include "torus.hpp"
#include "tiretexture.hpp"
#include "shader.hpp"
#include "utils.hpp"
#include "tire.hpp"

using std::shared_ptr;
using std::make_shared;

Tire::Tire(shared_ptr<Shader> shader, const RaceTrack &raceTrack, unsigned lane, float uStart,
           CollisionDetector &collisionDetector) :
        Object(shader, make_shared<Material>(), make_shared<TireTexture>(R, r, 900, 900), make_shared<Torus>(R, r)),
        raceTrack(raceTrack), lane(lane), uStart(uStart), collisionDetector(collisionDetector) {
    material->kd = vec3(0.1f, 0.1f, 0.1f);
    material->ks = vec3(2, 2, 2);
    material->ka = vec3(0.2f, 0.2f, 0.2f);
    material->shininess = 200;
    u = uStart;
}

void Tire::Animate(float tstart, float tend) {
    if (canAccelerate && speed < maxSpeed)
        speed += (tend - tstart) * acceleration;
    u += speed * (tend - tstart);
    if (u > 2.0f)
        u -= 2;
    SurfacePointData spd = raceTrack.GetData(u, lane);

    float currentR = R * scale.x;
    float currentr = r * scale.x;

    collisionDetector.ReportCurrentPosition(lane,
                                            vec2(u - (currentR + currentr) * 0.1f, u + (currentR + currentr) * 0.1f));

    translation = spd.position + spd.normal * (currentR + currentr);
    vec4 itrans(-spd.tangentU, 0);
    vec4 jtrans(spd.normal, 0);
    vec4 ktrans(spd.tangentV, 0);
    rollingPivot = spd.tangentV;

    rotationMatrix = mat4(itrans, jtrans, ktrans, vec4());

    rollingAngle = raceTrack.GetActualDistance(u) / (currentR + currentr);
}

mat4 Tire::GetM() const {
    return mat4::ScaleMatrix(scale) * rotationMatrix * mat4::RotationMatrix(rollingAngle, rollingPivot) *
           mat4::TranslateMatrix(translation);
}

mat4 Tire::GetMinv() const {
    return mat4::TranslateMatrix(-translation) * mat4::RotationMatrix(-rollingAngle, rollingPivot) *
           rotationMatrix.Transpose() * mat4::ScaleMatrix(vec3(1 / scale.x, 1 / scale.y, 1 / scale.z));
}

void Tire::StartAcceleration() {
    canAccelerate = true;
}