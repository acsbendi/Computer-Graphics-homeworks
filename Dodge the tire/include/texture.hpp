//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_TEXTURE_HPP
#define DODGE_THE_TIRE_TEXTURE_HPP

//---------------------------
class Texture {
//---------------------------
public:
    unsigned int textureId;

    Texture(int, int);

    void SetUniform(unsigned shaderProg, const char * samplerName, unsigned int textureUnit = 0);
};

#endif //DODGE_THE_TIRE_TEXTURE_HPP
