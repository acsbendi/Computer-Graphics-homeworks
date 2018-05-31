//
// Created by Bendi on 5/31/2018.
//

#include <memory>
#include "paraboloidfishtank.hpp"
#include "glass.hpp"

using std::make_unique;

ParaboloidFishTank::ParaboloidFishTank(vec3 center) : Intersectable{make_unique<Glass>()}, Paraboloid(center, make_unique<Glass>())
{}