//
// Created by Bendi on 5/26/2018.
//

#include "collisiondetector.hpp"
#include "tire.hpp"

CollisionDetector::CollisionDetector(unsigned int numberOfLanes, const vector<const Tire*> tires)
        : tires{tires} {}


bool CollisionDetector::CheckCollision(unsigned int lane, vec2 position) const {
    vec2 tirePosition = tires[lane]->GetPositionOnTrack(position.y);
    return tirePosition.x < position.x && position.x < tirePosition.y;
}

