//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_SCENE_H
#define DODGE_THE_TIRE_SCENE_H

#include <memory>
#include <vector>

using std::unique_ptr;
using std::vector;

class Object;
class Animatable;
class Tire;
class Camera;
class Light;

//---------------------------
class Scene {
//---------------------------
private:
    const unsigned int& windowWidth;
    const unsigned int& windowHeight;

    vector<unique_ptr<Object>> objects;
    vector<Animatable *> animatables;
    vector<Tire *> tires;
public:
    unique_ptr<Camera> camera; // 3D camera
    unique_ptr<Light> light;

    Scene(unsigned int&, unsigned int&);

    void Build();

    void Render();

    void Animate(float tstart, float tend);

    void StartMovingCamera();

    void SwitchCameraLane(bool right);

    void OnResize();

    ~Scene();
};

#endif //DODGE_THE_TIRE_SCENE_H
