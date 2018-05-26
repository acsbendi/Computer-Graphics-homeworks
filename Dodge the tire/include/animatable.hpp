//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_ANIMATABLE_HPP
#define DODGE_THE_TIRE_ANIMATABLE_HPP

class Animatable{
public:

    virtual void Animate(float tstart, float tend) = 0;

    virtual ~Animatable() = default;
};

#endif //DODGE_THE_TIRE_ANIMATABLE_HPP
