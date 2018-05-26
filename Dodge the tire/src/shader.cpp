//
// Created by Bendi on 5/26/2018.
//

#include "shader.hpp"
#include "opengl.hpp"
#include "cstdio"

void Shader::getErrorInfo(unsigned int handle) {
    int logLen, written;
    glGetShaderiv(handle, GL_INFO_LOG_LENGTH, &logLen);
    if (logLen > 0) {
        auto * log = new char[logLen];
        glGetShaderInfoLog(handle, logLen, &written, log);
        printf("Shader log:\n%s", log);
        delete log;
    }
}
void Shader::checkShader(unsigned int shader, const char * message) {  // check if shader could be compiled
    int OK;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &OK);
    if (!OK) { printf("%s!\n", message); getErrorInfo(shader); getchar(); }
}
void Shader::checkLinking(unsigned int program) {  // check if shader could be linked
    int OK;
    glGetProgramiv(program, GL_LINK_STATUS, &OK);
    if (!OK) { printf("Failed to link shader program!\n"); getErrorInfo(program); getchar(); }
}

void Shader::Create(const char * vertexSource, const char * fragmentSource, const char * fsOuputName) {
    // Create vertex shader from string
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if (!vertexShader) { printf("Error in vertex shader creation\n"); exit(1); }
    glShaderSource(vertexShader, 1, &vertexSource, nullptr);
    glCompileShader(vertexShader);
    checkShader(vertexShader, "Vertex shader error");

    // Create fragment shader from string
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!fragmentShader) { printf("Error in fragment shader creation\n"); exit(1); }
    glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentShader);
    checkShader(fragmentShader, "Fragment shader error");

    // Attach shaders to a single program
    shaderProgram = glCreateProgram();
    if (!shaderProgram) { printf("Error in shader program creation\n"); exit(1); }
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // Connect the fragmentColor to the frame buffer memory
    glBindFragDataLocation(shaderProgram, 0, fsOuputName); // fragmentColor goes to the frame buffer memory

    // program packaging
    glLinkProgram(shaderProgram);
    checkLinking(shaderProgram);
}

Shader::~Shader() { glDeleteProgram(shaderProgram); }