//
// Created by Bendi on 5/27/2018.
//

#ifndef BUTTERFLY_BUTTERFLY_WING_HPP
#define BUTTERFLY_BUTTERFLY_WING_HPP

#include "utils.hpp"
#include "butterfly.hpp"

class Butterfly::Wing {
private:
    static constexpr float m = 0.2;
    static constexpr unsigned int N = 2000;

    unsigned int vao, vbo[2], textureId;    // vertex array object id and texture id
    vec2 vertices[N], uvs[4];
    float phi;

    bool reverse;

    vec2 velocity;
    vec2 position;

    void createTexture();

public:
    Wing(bool reverse, vec2 headPosition);

    void create();

    void animate(float dt, float time);

    void draw();
};



#endif //BUTTERFLY_BUTTERFLY_WING_HPP
