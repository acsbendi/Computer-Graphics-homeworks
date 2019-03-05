//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_COLLISIONDETECTOR_HPP
#define DODGE_THE_TIRE_COLLISIONDETECTOR_HPP

#include <vector>
#include "utils.hpp"

using std::vector;

class Tire;

//---------------------------
class CollisionDetector{
//---------------------------
private:
    const vector<const Tire*> tires;

public:
    explicit CollisionDetector(unsigned int numberOfLanes,vector<const Tire*> tires);

    bool CheckCollision(unsigned int lane, vec2 position) const;
};

#endif //DODGE_THE_TIRE_COLLISIONDETECTOR_HPP
