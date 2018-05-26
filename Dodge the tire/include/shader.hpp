//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_SHADER_HPP
#define DODGE_THE_TIRE_SHADER_HPP

#include "renderstate.hpp"

//---------------------------
class Shader {
//--------------------------
    void getErrorInfo(unsigned int handle);
    void checkShader(unsigned int shader, const char * message);
    void checkLinking(unsigned int program);
protected:
    unsigned int shaderProgram;
public:
    void Create(const char * vertexSource, const char * fragmentSource, const char * fsOuputName);
    virtual void Bind(RenderState state) = 0;
    virtual ~Shader();
};

#endif //DODGE_THE_TIRE_SHADER_HPP
