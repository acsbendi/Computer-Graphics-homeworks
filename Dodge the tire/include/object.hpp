//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_OBJECT_HPP
#define DODGE_THE_TIRE_OBJECT_HPP

#include <memory>
#include "utils.hpp"
#include "renderstate.hpp"
#include "animatable.hpp"

using std::shared_ptr;

class Shader;
class Texture;
class Geometry;

//---------------------------
class Object : public Animatable{
//---------------------------

protected:
    virtual mat4 GetM() const;
    virtual mat4 GetMinv() const;

public:
    shared_ptr<Shader> shader;
    shared_ptr<Material> material;
    shared_ptr<Texture> texture;
    shared_ptr<Geometry> geometry;
    vec3 scale, translation, rotationAxis;
    float rotationAngle;

    Object(shared_ptr<Shader> _shader, shared_ptr<Material> _material, shared_ptr<Texture> _texture, shared_ptr<Geometry> _geometry);

    void Draw(RenderState state);

    void Animate(float tstart, float tend) override;
};

#endif //DODGE_THE_TIRE_OBJECT_HPP
