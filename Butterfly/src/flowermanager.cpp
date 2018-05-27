//
// Created by Bendi on 5/27/2018.
//

#include <memory>
#include "flowermanager.hpp"
#include "opengl.hpp"
#include "flower.hpp"

using std::make_unique;

FlowerManager::FlowerManager() noexcept = default;

void FlowerManager::create(){
    addFlower(1.1f,1.22f);
    addFlower(-3.1f,3.22f);
    addFlower(2.6f,-2.5f);
    addFlower(-3.6f,0.22f);
}

void FlowerManager::draw(){
    glUseProgram(shaderProgram);
    for (auto& flower : flowers) {
        flower->draw();
    }
}

void FlowerManager::addFlower(float x, float y){
    flowers.push_back(make_unique<Flower>(x,y));
    flowers.back()->create();
}

FlowerManager::~FlowerManager() = default;