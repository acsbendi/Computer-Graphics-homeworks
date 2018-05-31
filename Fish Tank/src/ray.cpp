//
// Created by Bendi on 5/30/2018.
//

#include "ray.hpp"

Ray::Ray(vec3 start, vec3 dir, bool out) :
        start{start}, dir{dir.normalize()}, out{out}
{}