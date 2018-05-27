//
// Created by Bendi on 5/27/2018.
//

#include <memory>
#include "butterfly.hpp"
#include "butterfly_body.hpp"
#include "butterfly_wing.hpp"

using std::make_unique;

Butterfly::Butterfly() noexcept : headPosition(0.0f,0.55f), leftWing(make_unique<Wing>(true,headPosition)),
                         rightWing(make_unique<Wing>(false,headPosition)), body(make_unique<Body>(headPosition)) { }

void Butterfly::animate(float dt, float time){
    leftWing->animate(dt, time);
    rightWing->animate(dt, time);
    body->animate(dt);
}

void Butterfly::draw(){
    leftWing->draw();
    rightWing->draw();
    body->draw();
}

void Butterfly::create(){
    leftWing->create();
    rightWing->create();
    body->create();
}

Butterfly::~Butterfly() = default;