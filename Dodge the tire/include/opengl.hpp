//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_OPENGL_HPP
#define DODGE_THE_TIRE_OPENGL_HPP

#if defined(__APPLE__)
#include <GLUT/GLUT.h>
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#else
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#include <windows.h>
#endif
#include <GL/glew.h>      // must be downloaded
#include <GL/freeglut.h>   // must be downloaded unless you have an Apple
#endif

#endif //DODGE_THE_TIRE_OPENGL_HPP
