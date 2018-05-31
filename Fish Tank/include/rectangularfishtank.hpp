//
// Created by Bendi on 5/30/2018.
//

#ifndef FISH_TANK_RECTANGULARFISHTANK_HPP
#define FISH_TANK_RECTANGULARFISHTANK_HPP

#include "room.hpp"
#include "fishtank.hpp"
#include "utils.hpp"

class RectangularFishTank : public Room, public FishTank {
public:
    explicit RectangularFishTank(vec3 vertex1 = vec3{-1.1f,1.1f,3.2f}, vec3 vertex2 = vec3{1.1f,-1.1f,-0.2f});
};

#endif //FISH_TANK_RECTANGULARFISHTANK_HPP

