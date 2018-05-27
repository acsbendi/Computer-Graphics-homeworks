//
// Created by Bendi on 5/27/2018.
//

#ifndef BUTTERFLY_OPENGL_HPP
#define BUTTERFLY_OPENGL_HPP

#if defined(__APPLE__)
#include <GLUT/GLUT.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#else
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#endif
#include <GL/glew.h>		// must be downloaded
#include <GL/freeglut.h>	// must be downloaded unless you have an Apple
#endif

extern unsigned int shaderProgram;
extern unsigned int textureShaderProgram;

#endif //BUTTERFLY_OPENGL_HPP
