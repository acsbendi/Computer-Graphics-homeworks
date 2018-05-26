//
// Created by Bendi on 5/26/2018.
//

#include "collisiondetector.hpp"

 CollisionDetector::CollisionDetector(unsigned int numberOfLanes){
    laneObjectPositions = vector<vec2>(numberOfLanes, vec2(0.0f,0.0f));
}


bool CollisionDetector::CheckCollision(unsigned int lane, float position) const {
    return laneObjectPositions[lane].x < position && laneObjectPositions[lane].y > position;
}

void CollisionDetector::ReportCurrentPosition(unsigned int lane, vec2 position){
    laneObjectPositions[lane] = position;
}

