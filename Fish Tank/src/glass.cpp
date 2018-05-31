//
// Created by Bendi on 5/30/2018.
//

#include "glass.hpp"

Glass::Glass() : Material(vec3(0.0f,0.0f,0.0f),vec3(0.0f,0.0f,0.0f),vec3(0.0f, 0.0f, 0.0f),0,vec3(1.5f, 1.5f, 1.5f)){
    rough = false;
    refractive = true;
    reflective = true;
}