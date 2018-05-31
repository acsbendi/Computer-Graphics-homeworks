//
// Created by Bendi on 5/30/2018.
//

#include "gold.hpp"

Gold::Gold() : Material(vec3(0.0f,0.0f,0.0f),vec3(0.0f,0.0f,0.0f),vec3(0.0f, 0.0f, 0.0f), 0,
                        vec3(0.17f, 0.35f, 1.5f), vec3(3.1f, 2.7f, 1.9f)){
    rough = false;
    reflective = true;
}