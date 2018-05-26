//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_TIRETEXTURE_HPP
#define DODGE_THE_TIRE_TIRETEXTURE_HPP

#include "texture.hpp"

//---------------------------
class TireTexture : public Texture{
//---------------------------
private:
    const float R, r;

public:
    TireTexture(const float R, const float r,const unsigned int width = 40, const unsigned int height = 40): Texture(width, height), R(R), r(r) {
        srand(1324534232);
        glBindTexture(GL_TEXTURE_2D, textureId);    // binding
        vector<vec3> image(width * height);
        const vec3 black(0, 0, 0);
        const vec3 darkGrey(0.3789f,0.3789f,0.3789f);
        const vec3 white(0.8941f, 0.9176f, 0.9176f);

        float ur, vr;
        for (unsigned int x = 0; x < width; x++)
            for (unsigned int y = 0; y < height; y++) {
                ur = (static_cast<float >(x) / width) * 2.0f * static_cast<float >(M_PI);
                vr = (static_cast<float >(y) / width) * 2.0f * static_cast<float >(M_PI);


                if(ur > M_PI + 0.6f && ur < 2* M_PI - 0.6f)
                    image[y * width + x] = white;
                else if(fabsf(ur - static_cast<float>(M_PI_2)) < 0.01f ||
                        fabsf(ur - (static_cast<float>(M_PI_2) + 0.35f)) < 0.01f || fabsf(ur - (static_cast<float>(M_PI_2) - 0.35f)) < 0.01f ||
                        fabsf(ur - (static_cast<float>(M_PI_2) + 0.7f)) < 0.01f || fabsf(ur - (static_cast<float>(M_PI_2) - 0.7f)) < 0.01f){
                    image[y * width + x] = black;
                } else if(ur > static_cast<float>(M_PI_4) && ur < static_cast<float>(M_PI_2) ){
                    image[y * width + x] = darkGrey;
                    float dummy;
                    float vrr = modff(vr/0.05f/static_cast<float>(M_PI)/2.0f,&dummy);

                    for(float offset = -1.0f; offset <= 1.0f; offset += 0.2f ){
                        if(fabsf((vrr + offset)/(ur - static_cast<float>(M_PI_4))/static_cast<float>(M_PI_4) - 1)  < 0.05f)
                            image[y * width + x] = black;
                    }

                } else if(ur < static_cast<float>(3*M_PI_4) && ur > static_cast<float>(M_PI_2) ){
                    image[y * width + x] = darkGrey;
                    float dummy;
                    float vrr = modff(vr/0.05f/static_cast<float>(M_PI)/2.0f,&dummy);

                    for(float offset = -1.0f; offset <= 1.0f; offset += 0.2f ){
                        if(fabsf((vrr + offset)/(static_cast<float>(3*M_PI_4) - ur)/static_cast<float>(M_PI_4) - 1)  < 0.05f)
                            image[y * width + x] = black;
                    }
                }
                else
                    image[y * width + x] = darkGrey;
            }
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, &image[0]); //Texture->OpenGL
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    }
};


#endif //DODGE_THE_TIRE_TIRETEXTURE_HPP
