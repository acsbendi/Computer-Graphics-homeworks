//
// Created by Bendi on 5/27/2018.
//

#ifndef BUTTERFLY_CATMULLROM_HPP
#define BUTTERFLY_CATMULLROM_HPP

#include <vector>
#include "utils.hpp"

using std::vector;

class CatmullRom {
private:
    std::vector<vec4> cps;		// control points
    std::vector<float>  ts;	// parameter (knot) values

    vec4 Hermite( vec4 p0, vec4 v0, float t0,
                  vec4 p1, vec4 v1, float t1,
                  float t ) const;

public:
    void AddControlPoint(vec4 cp, float t);

    vec4 r(float t) const;
};

#endif //BUTTERFLY_CATMULLROM_HPP
