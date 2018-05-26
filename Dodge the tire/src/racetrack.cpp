//
// Created by Bendi on 5/26/2018.
//

#include <memory>
#include "racetrack.hpp"
#include "shader.hpp"
#include "roadtexture.hpp"
#include "mobius.hpp"

using std::shared_ptr;
using std::make_shared;
using std::dynamic_pointer_cast;

RaceTrack::RaceTrack(shared_ptr<Shader> shader, shared_ptr<Material> material) : Object(move(shader), move(material), make_shared<RoadTexture>(4,200,200), make_shared<Mobius>(true, initialWidth)), width(initialWidth) {
        rotationAngle = 0;
        numberOfLanes = 4;
}

unsigned int RaceTrack::GetNumberOfLanes() const {
    return numberOfLanes;
}

float RaceTrack::GetActualDistance(float u) const{
    return scale.x * static_cast<float >(M_PI)*u;
}

void RaceTrack::Animate(float tstart, float tend) {  }

SurfacePointData RaceTrack::GetData(float u, int lane) const{
    float laneWidth = width/numberOfLanes;
    float v = laneWidth * lane + laneWidth/2;
    SurfacePointData spd = dynamic_pointer_cast<ParamSurface const>(geometry)->GenSurfacePointData(u,v/width);
    spd.position = static_cast<vec3>(vec4(spd.position) * GetM());
    spd.tangentV = static_cast<vec3>(vec4(spd.tangentV) * GetM()).normalize();
    spd.tangentU = static_cast<vec3>(vec4(spd.tangentU) * GetM()).normalize();
    spd.normal = static_cast<vec3>(GetMinv() *vec4(spd.normal) ).normalize();

    return spd;
}