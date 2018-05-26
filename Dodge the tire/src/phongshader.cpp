//
// Created by Bendi on 5/26/2018.
//

#include "phongshader.hpp"
#include "opengl.hpp"
#include "light.hpp"
#include "texture.hpp"

PhongShader::PhongShader() { Create(vertexSource, fragmentSource, "fragmentColor"); }

void PhongShader::Bind(RenderState state){
    glUseProgram(shaderProgram);      // make this program run
    state.MVP.SetUniform(shaderProgram, "MVP");
    state.M.SetUniform(shaderProgram, "M");
    state.Minv.SetUniform(shaderProgram, "Minv");
    state.wEye.SetUniform(shaderProgram, "wEye");
    state.material->kd.SetUniform(shaderProgram, "kd");
    state.material->ks.SetUniform(shaderProgram, "ks");
    state.material->ka.SetUniform(shaderProgram, "ka");
    int location = glGetUniformLocation(shaderProgram, "shine");
    if (location >= 0) glUniform1f(location, state.material->shininess);
    else
        printf("uniform shininess cannot be set\n");
    state.light->La.SetUniform(shaderProgram, "La");
    state.light->Le.SetUniform(shaderProgram, "Le");
    state.light->wLightPos.SetUniform(shaderProgram, "wLiPos");
    state.texture->SetUniform(shaderProgram, "diffuseTexture");
}