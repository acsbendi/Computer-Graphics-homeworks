//
// Created by Bendi on 5/26/2018.
//

#include <cstdlib>
#include <cmath>
#include "opengl.hpp"
#include "utils.hpp"
#include "roadtexture.hpp"
#include "texture.hpp"

RoadTexture::RoadTexture(const unsigned int numberOfLanes, const unsigned int width = 40, const unsigned int height = 40) :
        Texture(width, height), width(width), height(height) {
    srand(437482354);
    glBindTexture(GL_TEXTURE_2D, textureId);    // binding

    float elementaryLaneWidth = static_cast<float>(height)/(numberOfLanes * laneWidth + (numberOfLanes - 1) * yellowLineWidth);
    image = vector<vec3>(width * height);
    for (unsigned int x = 0; x < width; x++)
        for (unsigned int y = 0; y < height; y++){
            float laneY;
            modff(y/ elementaryLaneWidth,&laneY);
            if(static_cast<int>(laneY)%5 >= 4 /*&& x % 20 < yellowLineLength*/ )
                image[y * width + x] = yellowLine;
            else
                image[y * width + x] = asphalt;
        }



    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, &image[0]); //Texture->OpenGL
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
