//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_RACETRACK_HPP
#define DODGE_THE_TIRE_RACETRACK_HPP

#include <memory>
#include "utils.hpp"
#include "object.hpp"

using std::shared_ptr;

class Shader;
class Material;

class RaceTrack : public Object{
private:
    static constexpr float initialWidth = 0.8f;

    unsigned int numberOfLanes;
    float width;

public:
    explicit RaceTrack(shared_ptr<Shader> shader, shared_ptr<Material> material);

    unsigned int GetNumberOfLanes() const;

    float GetActualDistance(float u) const;

    void Animate(float tstart, float tend) override;

    SurfacePointData GetData(float u, int lane) const;

};

#endif //DODGE_THE_TIRE_RACETRACK_HPP
