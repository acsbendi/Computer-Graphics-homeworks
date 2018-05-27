//
// Created by Bendi on 5/27/2018.
//

#ifndef BUTTERFLY_PETALS_HPP
#define BUTTERFLY_PETALS_HPP

#include <vector>
#include "flower.hpp"

using std::vector;

class FlowerManager::Flower::Petals{
    unsigned int vao;	// vertex array object id
    vector<float> vertexCoords;
    vector<float> vertexColors;
    const float R;
    const float X;
    const float Y;
    const unsigned int petalCount;

    static constexpr unsigned int N = 200;

    void CreateVertex();

public:
    Petals(float r, float x, float y);

    void create();

    void draw();

    unsigned int getNextFibonacci();

};

#endif //BUTTERFLY_PETALS_HPP
