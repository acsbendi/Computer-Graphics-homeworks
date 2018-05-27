//
// Created by Bendi on 5/27/2018.
//

#ifndef BUTTERFLY_UTILS_HPP
#define BUTTERFLY_UTILS_HPP

#include "cmath"

// row-major matrix 4x4
struct mat4 {
    float m[4][4];
public:
    mat4() = default;
    mat4(float m00, float m01, float m02, float m03,
         float m10, float m11, float m12, float m13,
         float m20, float m21, float m22, float m23,
         float m30, float m31, float m32, float m33) : m{m[4][4]} {
        m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
        m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
        m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
        m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
    }

    mat4 operator*(const mat4& right) {
        mat4 result{};
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i][j] = 0;
                for (int k = 0; k < 4; k++) result.m[i][j] += m[i][k] * right.m[k][j];
            }
        }
        return result;
    }
    explicit operator float*() { return &m[0][0]; }
};

// 3D point in homogeneous coordinates
struct vec4 {
    float v[4];

    explicit vec4(float x = 0, float y = 0, float z = 0, float w = 1) : v{v[4]} {
        v[0] = x; v[1] = y; v[2] = z; v[3] = w;
    }

    vec4 operator*(const mat4& mat) const {
        vec4 result;
        for (int j = 0; j < 4; j++) {
            result.v[j] = 0;
            for (int i = 0; i < 4; i++) result.v[j] += v[i] * mat.m[i][j];
        }
        return result;
    }

    vec4 operator-(const vec4& other) const{
        return vec4(v[0] - other.v[0], v[1] - other.v[1], v[2] - other.v[2],v[3] - other.v[3]);
    }

    vec4 operator+(const vec4& other) const{
        return vec4(v[0] + other.v[0], v[1] + other.v[1], v[2] + other.v[2], v[3] + other.v[3]);
    }

    vec4 operator*(float f) const{
        return vec4(v[0]*f, v[1]*f, v[2]*f, v[3]*f);
    }

    float distance(const vec4& other) const{
        return sqrtf((v[0]-other.v[0])*(v[0]-other.v[0]) + (v[1]-other.v[1])*(v[1]-other.v[1])+ (v[2]-other.v[2])*(v[2]-other.v[2])+ (v[3]-other.v[3])*(v[3]-other.v[3]));
    }
};

struct vec2 {
    float x, y;
    explicit vec2(float _x = 0.0f, float _y = 0.0f) noexcept { x = _x; y = _y; }

    explicit vec2(const vec4& hom) { x = hom.v[0] / hom.v[3]; y = hom.v[1] / hom.v[3]; }

    vec2 operator*(float f){
        return vec2{f*x,f*y};
    }

    vec2 operator/(float f){
        return vec2{x/f,y/f};
    }

    vec2 operator+(const vec2& v){
        return vec2{x + v.x,y + v.y};
    }

    vec2 operator-(const vec2& v){
        return vec2{x - v.x,y - v.y};
    }

    vec2 operator+=(const vec2& v){
        *this = *this + v;
        return *this;
    }

    float length() const{
        return sqrtf(x*x + y*y);
    }

    float distance(const vec2& v) const{
        return sqrtf((x-v.x)*(x-v.x) + (y-v.y)*(y-v.y));
    }
};

// 3D point in Cartesian coordinates or RGB color
struct vec3 {
    float x, y, z;

    explicit vec3(const vec2& v){
        x = v.x;
        y = v.y;
        z = 0.0f;
    }

    explicit vec3(float _x = 0, float _y = 0, float _z = 0) {
        x = _x;
        y = _y;
        z = _z;
    }

    vec3 operator+=(const vec3& v){
        *this = vec3(x+v.x,y+v.y,z+v.z);
        return *this;
    }

    vec3 operator/(float f){
        return vec3{x/f,y/f,z/f};
    }

    vec3 operator*(float f){
        return vec3{f*x,f*y,f*z};
    }

    vec3 operator-(const vec3& v){
        return vec3{x - v.x,y - v.y,z - v.z};
    }

    vec3 cross(const vec3& v){
        return vec3{y*v.z - z*v.y,z*v.x - x*v.z, x*v.y - y*v.x};
    }

    float length(){
        return sqrtf(x*x + y*y + z*z);
    }
};

#endif //BUTTERFLY_UTILS_HPP
