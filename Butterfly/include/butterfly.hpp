//
// Created by Bendi on 5/27/2018.
//

#ifndef BUTTERFLY_BUTTERFLY_HPP
#define BUTTERFLY_BUTTERFLY_HPP

#include <memory>
#include "utils.hpp"

using std::unique_ptr;

class Butterfly{
private:

    class Wing;

    class Body;

    const vec2 headPosition;

    unique_ptr<Wing> leftWing;
    unique_ptr<Wing> rightWing;
    unique_ptr<Body> body;

public:
    Butterfly() noexcept ;

    void animate(float dt, float time);

    void draw();

    void create();

    ~Butterfly();
};


#endif //BUTTERFLY_BUTTERFLY_HPP
