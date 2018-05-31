//
// Created by Bendi on 5/31/2018.
//

#include <memory>
#include "rectangularfishtank.hpp"
#include "glass.hpp"

using std::make_unique;

RectangularFishTank::RectangularFishTank(vec3 vertex1, vec3 vertex2) :
        Room(vertex1,vertex2,make_unique<Glass>())
{}