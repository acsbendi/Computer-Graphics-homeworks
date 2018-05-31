//
// Created by Bendi on 5/30/2018.
//

#ifndef FISH_TANK_MATERIAL_HPP
#define FISH_TANK_MATERIAL_HPP

#include "utils.hpp"

class Material {
protected:
    const vec3 kd, ks;
    const float shininess;

    const vec3 refractiveIndex;
    const vec3 extinctionCoefficient;
public:
    vec3 ka;
    bool rough;
    bool reflective;
    bool refractive;
    Material(vec3 _ka, vec3 _kd, vec3 _ks, float _shininess,
             vec3 refractiveIndex = vec3(0,0,0), vec3 extinctionCoefficient = vec3(0,0,0));

    vec3 shade(vec3 normal, vec3 viewDir, vec3 lightDir, vec3 inRad);

    vec3 fresnelApprox(const vec3& inDir, const vec3& normal);
};


#endif //FISH_TANK_MATERIAL_HPP
