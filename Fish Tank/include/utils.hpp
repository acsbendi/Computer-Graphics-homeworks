//
// Created by Bendi on 5/30/2018.
//

#ifndef TEXTURE_TEST_UTILS_HPP
#define TEXTURE_TEST_UTILS_HPP

#include <cmath>

struct vec3 {
    float x, y, z;
    explicit vec3(float x0 = 0, float y0 = 0, float z0 = 0) : x(x0), y(y0), z(z0) {  }
    vec3 operator*(float a) const { return vec3(x * a, y * a, z * a); }
    vec3 operator/(float d) const { return vec3(x / d, y / d, z / d); }
    vec3 operator+(const vec3& v) const { return vec3(x + v.x, y + v.y, z + v.z); }
    void operator+=(const vec3& v) { x += v.x; y += v.y; z += v.z; }
    vec3 operator-(const vec3& v) const { return vec3(x - v.x, y - v.y, z - v.z); }
    vec3 operator*(const vec3& v) const { return vec3(x * v.x, y * v.y, z * v.z); }
    vec3 operator/(const vec3& v) const { return vec3(x / v.x, y / v.y, z / v.z); }
    vec3 operator-() const { return vec3(-x, -y, -z); }
    vec3 normalize() const { return (*this) * (1 / (length() + 0.000001)); }
    float length() const { return sqrtf(x * x + y * y + z * z); }
    explicit operator float*() { return &x; }
};

inline float dot(const vec3& v1, const vec3& v2) {
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

inline vec3 cross(const vec3& v1, const vec3& v2) {
    return vec3{v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x};
}

inline vec3 reflect(const vec3& inDir, const vec3& normal){
    return inDir + normal*2.0f*dot(-inDir,normal);
}

inline vec3 refract(const vec3& inDir, const vec3& normal, float n){
    float cosAlpha = dot(-inDir,normal);
    float sinAlpha2 = 1-cosAlpha*cosAlpha;
    if(sinAlpha2/n/n > 1.0f)
        return vec3{};
    float cosBeta = sqrtf(1-sinAlpha2/n/n);
    return inDir/n + normal*(cosAlpha/n - cosBeta);
}


#endif //TEXTURE_TEST_UTILS_HPP
