//
// Created by Bendi on 5/30/2018.
//

#ifndef FISH_TANK_PARABOLOIDFISHTANK_HPP
#define FISH_TANK_PARABOLOIDFISHTANK_HPP

#include "paraboloid.hpp"
#include "fishtank.hpp"
#include "utils.hpp"

class ParaboloidFishTank : public Paraboloid, public FishTank {
public:
    explicit ParaboloidFishTank(vec3 center = vec3{0.0f,-0.5f,0.0f});
};


#endif //FISH_TANK_PARABOLOIDFISHTANK_HPP
