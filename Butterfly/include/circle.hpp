//
// Created by Bendi on 5/27/2018.
//

#ifndef BUTTERFLY_CIRCLE_HPP
#define BUTTERFLY_CIRCLE_HPP

#include <vector>
#include "flower.hpp"

class FlowerManager::Flower::Circle{

    unsigned int vao;	// vertex array object id
    vector<float> vertexCoords;
    vector<float> vertexColors;
    const float R;
    const float X;
    const float Y;


    static constexpr unsigned int N = 200;

    void CreateVertex();

public:
    Circle(float r, float x, float y);

    void create();

    void draw();
};

#endif //BUTTERFLY_CIRCLE_HPP
