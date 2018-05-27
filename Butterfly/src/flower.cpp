//
// Created by Bendi on 5/27/2018.
//

#include <memory>
#include "flower.hpp"
#include "petals.hpp"
#include "circle.hpp"

using std::make_unique;

FlowerManager::Flower::Flower(float x, float y) : circle(make_unique<Circle>(R,x,y)), petals(make_unique<Petals>(R,x,y)) {

}

void FlowerManager::Flower::create(){
    petals->create();
    circle->create();
}

void FlowerManager::Flower::draw(){
    petals->draw();
    circle->draw();
}

FlowerManager::Flower::~Flower() = default;