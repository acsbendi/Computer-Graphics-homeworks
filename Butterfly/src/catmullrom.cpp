//
// Created by Bendi on 5/27/2018.
//

#include "catmullrom.hpp"

vec4 CatmullRom::Hermite( vec4 p0, vec4 v0, float t0,
              vec4 p1, vec4 v1, float t1,
              float t ) const {
    vec4 a0 = p0;
    vec4 a1 = v0;
    vec4 a2 = (p1-p0)*3*(1/((t1-t0)*(t1-t0))) - ((v1 + v0*2)*(1/(t1-t0)));
    vec4 a3 = (p0-p1)*2*(1/((t1-t0)*(t1-t0)*(t1-t0))) + (v1 + v0)*(1/((t1-t0)*(t1-t0)));

    return a3*((t-t0)*(t-t0)*(t-t0)) + a2*((t-t0)*(t-t0)) + a1*(t-t0) + a0;
}

void CatmullRom::AddControlPoint(vec4 cp, float t) {
    cps.push_back(cp);
    ts.push_back(t);
}

vec4 CatmullRom::r(float t) const {
    for(int i = 0; i < cps.size() - 1; i++) {
        if (ts[i] <= t && t <= ts[i+1]) {
            vec4 v0, v1;

            if(i == 0 && cps[0].distance(cps.back()) < 0.001f)
                v0 = ( (cps[i+1] - cps[i])*(1/(ts[i+1] - ts[i])) + (cps[i] - cps.back())*(1/(ts[i] - ts.back())))*0.5f;
            else if(i == 0)
                v0 = vec4(0.50f,0.50f);
            else
                v0 = ( (cps[i+1] - cps[i])*(1/(ts[i+1] - ts[i])) + (cps[i] - cps[i-1])*(1/(ts[i] - ts[i-1])))*0.5f;

            if(i == cps.size() - 2 && cps[0].distance(cps.back()) < 0.001f)
                v1 = ( (cps[0] - cps[i+1])*(1/(ts[0] - ts[i+1])) + (cps[i+1] - cps[i])*(1/(ts[i+1] - ts[i])))*0.5f;
            else if(i == cps.size() - 2)
                v1 = vec4(0.50f,0.50f);
            else
                v1 = ( (cps[i+2] - cps[i+1])*(1/(ts[i+2] - ts[i+1])) + (cps[i+1] - cps[i])*(1/(ts[i+1] - ts[i])))*0.5f;
            return Hermite(cps[i],v0,ts[i],cps[i+1],v1,ts[i+1],t);
        }
    }
}