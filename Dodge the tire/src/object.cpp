//
// Created by Bendi on 5/26/2018.
//

#include <memory>
#include <object.hpp>
#include <utils.hpp>
#include <renderstate.hpp>
#include <shader.hpp>
#include <geometry.hpp>

using std::shared_ptr;
using std::move;

mat4 Object::GetM() const {
    return mat4::ScaleMatrix(scale) * mat4::RotationMatrix(rotationAngle, rotationAxis) * mat4::TranslateMatrix(translation);
}

mat4 Object::GetMinv() const{
    return mat4::TranslateMatrix(-translation) * mat4::RotationMatrix(-rotationAngle, rotationAxis) * mat4::ScaleMatrix(vec3(1 / scale.x, 1 / scale.y, 1 / scale.z));
}

Object::Object(shared_ptr<Shader> _shader, shared_ptr<Material> _material, shared_ptr<Texture> _texture, shared_ptr<Geometry> _geometry) :
scale(vec3(1, 1, 1)), translation(vec3(0, 0, 0)), rotationAxis(0, 0, 1), rotationAngle(0) {
    shader = move(_shader);
    texture = move(_texture);
    material = move(_material);
    geometry = move(_geometry);
}

void Object::Draw(RenderState state) {
    state.M = GetM();
    state.Minv = GetMinv() ;
    state.MVP = state.M * state.V * state.P;
    state.material = material.get();
    state.texture = texture.get();
    shader->Bind(state);
    geometry->Draw();
}

void Object::Animate(float tstart, float tend) { //rotationAngle = 0.8f * tend;
}