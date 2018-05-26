//
// Created by Bendi on 5/26/2018.
//

#include <cstdio>
#include "opengl.hpp"
#include "texture.hpp"

Texture::Texture(const int width, const int height) {  glGenTextures(1, &textureId); }

void Texture::SetUniform(unsigned shaderProg, const char * samplerName, unsigned int textureUnit) {
    int location = glGetUniformLocation(shaderProg, samplerName);
    if (location >= 0) {
        glUniform1i(location, textureUnit);
        glActiveTexture(GL_TEXTURE0 + textureUnit);
        glBindTexture(GL_TEXTURE_2D, textureId);
    } else printf("uniform %s cannot be set\n", samplerName);
}