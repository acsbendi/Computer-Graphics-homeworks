//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_ROADTEXTURE_HPP
#define DODGE_THE_TIRE_ROADTEXTURE_HPP

#include <vector>
#include "texture.hpp"

using std::vector;

class RoadTexture : public Texture {
private:
    vector<vec3> image;
    const vec3 asphalt = vec3(0.092157f, 0.12941f, 0.14902f);
    const vec3 yellowLine = vec3(0.92157f, 0.76471f, 0.00784f);

    const unsigned int width, height;

    static constexpr unsigned int laneWidth = 4;
    static constexpr unsigned int yellowLineWidth = 1;
    /*static constexpr unsigned int yellowLineLength = 10;*/

public:
    RoadTexture(unsigned int, unsigned int, unsigned int);
};


#endif //DODGE_THE_TIRE_ROADTEXTURE_HPP
