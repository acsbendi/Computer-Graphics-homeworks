//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_SKYTEXTURE_HPP
#define DODGE_THE_TIRE_SKYTEXTURE_HPP

#include <vector>
#include "utils.hpp"
#include "texture.hpp"

using std::vector;

class SkyTexture : public Texture {
private:
    vector<vec3> image;
    const vec3 blue = vec3(0.25098f, 0.45098f, 0.87843f);
    const vec3 cloudColors[6] { vec3(0.93725f,0.95686f,0.97255f), vec3(0.85f,0.9f,0.96275f),vec3(0.76098f,0.85980f,0.96275f),
                                vec3(0.79216f,0.89412f,1.0f), vec3(0.65216f,0.78412f,0.97f),vec3(0.44314f,0.65098f,0.95686f)};
    const vec3 sunColors[6] { vec3(1.0f,1.0f,1.0f), vec3(0.99627f,0.98588f,0.95294f),vec3(0.99216f,0.9451f,0.85392f),
                              vec3(0.98216f,0.91412f,0.80f), vec3(0.97016f,0.89412f,0.650f),vec3(0.96078f,0.87451f,0.5f)};

    const unsigned int width, height;
    const unsigned int cloudR;
    const unsigned int sunR;

    float probabilityDecreaseFactor = 0.7f;
    static constexpr float nextDistanceFactor = 0.6f;

    enum Direction{left, right, up, down, any};

    inline void FillCloudCircle(unsigned int x, unsigned int y, float probability, Direction direction);

    void FillCircle(unsigned int x, unsigned int y, const vec3 colorArray[6], int R);

public:
    explicit SkyTexture(unsigned int width = 40,unsigned int height = 40);
};


#endif //DODGE_THE_TIRE_SKYTEXTURE_HPP
