//
// Created by Bendi on 5/30/2018.
//

#include "material.hpp"

Material::Material(vec3 _ka, vec3 _kd, vec3 _ks, float _shininess,
                   vec3 refractiveIndex, vec3 extinctionCoefficient) :
        ka(_ka), kd(_kd), ks(_ks), rough(true),
        reflective(false), refractive(false), shininess(_shininess),
        extinctionCoefficient(extinctionCoefficient),  refractiveIndex(refractiveIndex)
{  }

vec3 Material::shade(vec3 normal, vec3 viewDir, vec3 lightDir, vec3 inRad) {
    vec3 reflRad(0, 0, 0);
    float cosTheta = dot(normal, lightDir);
    if (cosTheta < 0) return reflRad;
    reflRad = inRad * kd * cosTheta;
    vec3 halfway = (viewDir + lightDir).normalize();
    float cosDelta = dot(normal, halfway);
    if (cosDelta < 0) return reflRad;
    return reflRad + inRad * ks * powf(cosDelta, shininess);
}


vec3 Material::fresnelApprox(const vec3& inDir, const vec3& normal){
    vec3 one = vec3(1,1,1);
    vec3 F0 = ((refractiveIndex - one)*(refractiveIndex - one) + extinctionCoefficient * extinctionCoefficient) /
              ((refractiveIndex + one)*(refractiveIndex + one) + extinctionCoefficient * extinctionCoefficient);
    float cosAlpha = dot(-inDir,normal);
    return F0 + (one - F0)*powf(1-cosAlpha,5);
}