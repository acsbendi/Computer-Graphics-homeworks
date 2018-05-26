//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_UTILS_HPP
#define DODGE_THE_TIRE_UTILS_HPP

#include <cmath>
#include <cstdio>
#include "opengl.hpp"

//---------------------------
struct vec2 {
//---------------------------
    float x, y;
    vec2(float _x = 0, float _y = 0) { x = _x; y = _y; }
};

//---------------------------
struct vec3 {
//---------------------------
    float x, y, z;
    vec3(float _x = 0, float _y = 0, float _z = 0) { x = _x; y = _y; z = _z; }
    vec3 operator*(float a) const { return vec3(x * a, y * a, z * a); }
    vec3 operator+(const vec3& v) const { return vec3(x + v.x, y + v.y, z + v.z); }
    vec3 operator-(const vec3& v) const { return vec3(x - v.x, y - v.y, z - v.z); }
    vec3 operator*(const vec3& v) const { return vec3(x * v.x, y * v.y, z * v.z); }
    vec3 operator-() const { return vec3(-x, -y, -z); }
    vec3 normalize() const { return (*this) * (1.0f / (Length() + 0.000001)); }
    float Length() const { return sqrtf(x * x + y * y + z * z); }

    void SetUniform(unsigned shaderProg, const char * name) {
        int location = glGetUniformLocation(shaderProg, name);
        if (location >= 0) glUniform3fv(location, 1, &x);
        else printf("uniform %s cannot be set\n", name);
    }

    float Lightness() const{
        return x + y + z;
    }

    inline static float dot(const vec3& v1, const vec3& v2) { return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z); }

    inline static vec3 cross(const vec3& v1, const vec3& v2) { return vec3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x); }
};

struct mat4;

//---------------------------
struct vec4 {
//---------------------------
    float x, y, z, w;
    vec4(float _x = 0, float _y = 0, float _z = 0, float _w = 1) { x = _x; y = _y; z = _z; w = _w; }
    vec4(vec3 v, float w = 1) : w(w){
        x = v.x;
        y = v.y;
        z = v.z;
    }

    explicit operator vec3(){
        return vec3(x,y,z);
    }

    inline vec4 operator*(const mat4& mat);

    void SetUniform(unsigned shaderProg, const char * name) {
        int location = glGetUniformLocation(shaderProg, name);
        if (location >= 0) glUniform4fv(location, 1, &x);
        else printf("uniform %s cannot be set\n", name);
    }
};

//---------------------------
struct mat4 { // row-major matrix 4x4
//---------------------------
    float m[4][4];
public:
    mat4() {}
    mat4(float m00, float m01, float m02, float m03,
         float m10, float m11, float m12, float m13,
         float m20, float m21, float m22, float m23,
         float m30, float m31, float m32, float m33) {
        m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
        m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
        m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
        m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
    }

    mat4(const vec4& v1, const vec4& v2, const vec4& v3, const vec4& v4){
        m[0][0] = v1.x; m[0][1] = v1.y; m[0][2] = v1.z; m[0][3] = v1.w;
        m[1][0] = v2.x; m[1][1] = v2.y; m[1][2] = v2.z; m[1][3] = v2.w;
        m[2][0] = v3.x; m[2][1] = v3.y; m[2][2] = v3.z; m[2][3] = v3.w;
        m[3][0] = v4.x; m[3][1] = v4.y; m[3][2] = v4.z; m[3][3] = v4.w;
    }

    inline mat4 operator*(const mat4& right) {
        mat4 result;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                result.m[i][j] = 0;
                for (int k = 0; k < 4; k++) result.m[i][j] += m[i][k] * right.m[k][j];
            }
        }
        return result;
    }

    inline vec4 operator*(const vec4& vec) {
        float result[4]{0};
        for (int k = 0; k < 4; k++) {
            result[k] += vec.x * m[k][0];
            result[k] += vec.y * m[k][1];
            result[k] += vec.z * m[k][2];
            result[k] += vec.w * m[k][3];

        }
        return vec4(result[0],result[1],result[2],result[3]);
    }

    mat4 Transpose() const{
        return mat4(m[0][0],m[1][0],m[2][0],m[3][0],
                    m[0][1],m[1][1],m[2][1],m[3][1],
                    m[0][2],m[1][2],m[2][2],m[3][2],
                    m[0][3],m[1][3],m[2][3],m[3][3]);
    }

    void SetUniform(unsigned shaderProg, const char * name) {
        int location = glGetUniformLocation(shaderProg, name);
        if (location >= 0) glUniformMatrix4fv(location, 1, GL_TRUE, m[0]);
        else printf("uniform %s cannot be set\n", name);
    }

    static mat4 TranslateMatrix(vec3 t) {
        return mat4(1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    t.x, t.y, t.z, 1);
    }

    static mat4 ScaleMatrix(vec3 s) {
        return mat4(s.x, 0, 0, 0,
                    0, s.y, 0, 0,
                    0, 0, s.z, 0,
                    0, 0, 0, 1);
    }

    static mat4 RotationMatrix(float angle, vec3 w) {
        float c = cosf(angle), s = sinf(angle);
        w = w.normalize();
        return mat4(c * (1 - w.x*w.x) + w.x*w.x, w.x*w.y*(1 - c) + w.z*s,     w.x*w.z*(1 - c) - w.y*s,     0,
                    w.x*w.y*(1 - c) - w.z*s,     c * (1 - w.y*w.y) + w.y*w.y, w.y*w.z*(1 - c) + w.x*s,     0,
                    w.x*w.z*(1 - c) + w.y*s,     w.y*w.z*(1 - c) - w.x*s,     c * (1 - w.z*w.z) + w.z*w.z, 0,
                    0,                           0,                           0,                           1);
    }
};

vec4 vec4::operator*(const mat4& mat) {
    float result[4]{0};
    for (int k = 0; k < 4; k++) {
        result[k] += x * mat.m[0][k];
        result[k] += y * mat.m[1][k];
        result[k] += z * mat.m[2][k];
        result[k] += w * mat.m[3][k];

    }
    return vec4(result[0],result[1],result[2],result[3]);
}

//---------------------------
struct Material {
//---------------------------
    vec3 kd, ks, ka;
    float shininess = 0;
};

//---------------------------
struct VertexData {
//---------------------------
    vec3 position, normal;
    vec2 texcoord;
};

//---------------------------
struct SurfacePointData{
//---------------------------
    vec3 position;
    vec3 normal;
    vec3 tangentU;
    vec3 tangentV;
};

#endif //DODGE_THE_TIRE_UTILS_HPP
