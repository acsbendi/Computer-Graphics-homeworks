//
// Created by Bendi on 5/27/2018.
//

#ifndef BUTTERFLY_BUTTERFLY_BODY_HPP
#define BUTTERFLY_BUTTERFLY_BODY_HPP

#include "utils.hpp"
#include "butterfly.hpp"

class Butterfly::Body{
    private:
        static constexpr float m = 0.2;
        static constexpr unsigned int N = 2000;

        unsigned int vao, vbo[2];
        vec2 vertices[N];
        vec3 colors[N];

        vec2 velocity;
        vec2 position;

        const vec3 middleColor = vec3(0.2588f,0.1372f,0.0f);
        const vec3 color = vec3(0.6471f,0.3451f,0.01f);

    public:
        explicit Body(vec2 headPosition);

        void create( );

        void animate(float dt);

        void draw();
    };


#endif //BUTTERFLY_BUTTERFLY_BODY_HPP
