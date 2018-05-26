//
// Created by Bendi on 5/26/2018.
//

#include "geometry.hpp"
#include "opengl.hpp"

Geometry::Geometry(unsigned int _type) {
    type = _type;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void Geometry::Draw() {
    glBindVertexArray(vao);
    glDrawArrays(type, 0, nVertices);
}

Geometry::~Geometry() = default;