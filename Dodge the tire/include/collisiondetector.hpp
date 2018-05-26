//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_COLLISIONDETECTOR_HPP
#define DODGE_THE_TIRE_COLLISIONDETECTOR_HPP

#include <vector>
#include "utils.hpp"

using std::vector;

//---------------------------
class CollisionDetector{
//---------------------------
private:
    vector<vec2> laneObjectPositions;
    //TODO implement pull model and improve precision by checking height

public:
    explicit CollisionDetector(unsigned int numberOfLanes);

    bool CheckCollision(unsigned int lane, float position) const;

    void ReportCurrentPosition(unsigned int lane, vec2 position);
};

#endif //DODGE_THE_TIRE_COLLISIONDETECTOR_HPP
