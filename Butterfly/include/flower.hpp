//
// Created by Bendi on 5/27/2018.
//

#ifndef BUTTERFLY_FLOWER_HPP
#define BUTTERFLY_FLOWER_HPP

#include <memory>
#include "flowermanager.hpp"

using std::unique_ptr;

class FlowerManager::Flower{
private:
   class Circle;

    class Petals;

    unique_ptr<Circle> circle;
    unique_ptr<Petals> petals;

    static constexpr float R = 0.3f;
public:
    Flower(float x, float y);

    void create();

    void draw();

    ~Flower();
};

#endif //BUTTERFLY_FLOWER_HPP
