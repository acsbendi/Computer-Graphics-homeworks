//
// Created by Bendi on 5/26/2018.
//

#include <memory>
#include "scene.hpp"
#include "utils.hpp"
#include "shader.hpp"
#include "phongshader.hpp"
#include "light.hpp"
#include "renderstate.hpp"
#include "racetrack.hpp"
#include "skytexture.hpp"
#include "sphere.hpp"
#include "object.hpp"
#include "collisiondetector.hpp"
#include "tire.hpp"
#include "camera.hpp"
#include "animatable.hpp"

using std::shared_ptr;
using std::make_shared;
using std::make_unique;

void Scene::Build() {
    // Shaders
    shared_ptr<Shader> phongShader = make_shared<PhongShader>();

    // Materials
    shared_ptr<Material> material0 = make_shared<Material>();
    material0->kd = vec3(0.0f, 0.0f, 0.0f);
    material0->ks = vec3(0, 0, 0);
    material0->ka = vec3(1.0f, 1.0f, 1.0f);
    material0->shininess = 50;

    shared_ptr<Material> material1 = make_shared<Material>();
    material1->kd = vec3(1, 1, 1);
    material1->ks = vec3(0.2f, 0.2f, 0.2f);
    material1->ka = vec3(0.2f, 0.2f, 0.2f);
    material1->shininess = 200;

    unique_ptr<Object> spaceBackground = make_unique<Object>(phongShader, material0, make_shared<SkyTexture>(2000,2000), make_shared<Sphere>());
    spaceBackground->translation = vec3(0, 0, 0);
    spaceBackground->rotationAxis = vec3(1, 1, 1);
    spaceBackground->rotationAngle = 0;
    spaceBackground->scale = vec3(5.5f, 5.5f, 5.5f);


    unique_ptr<RaceTrack> raceTrack = make_unique<RaceTrack>(phongShader, material0);
    unique_ptr<CollisionDetector> collisionDetector = make_unique<CollisionDetector>(raceTrack->GetNumberOfLanes());

    for(unsigned int i = 0; i < raceTrack->GetNumberOfLanes(); i++){
        unique_ptr<Tire> tire = make_unique<Tire>(phongShader,*raceTrack,i,static_cast<float>(i)/5,*collisionDetector);
        tire->scale = vec3(0.2f, 0.2f, 0.2f);
        tires.push_back(tire.get());
        animatables.push_back(tire.get());
        objects.push_back(move(tire));
    }

    // Camera
    camera = make_unique<Camera>(*raceTrack,vec3(0,0,3),vec3(0,0,0),vec3(0,1,0),collisionDetector,windowWidth,windowHeight);
    objects.push_back(move(raceTrack));
    objects.push_back(move(spaceBackground));
    animatables.push_back(camera.get());

    // Light
    light = make_unique<Light>();
    light->wLightPos = vec4(-1, 1, 5, 0);    // ideal point -> directional light source
    light->La = vec3(1.1f, 1.1f, 1.1f);
    light->Le = vec3(3, 3, 3);
}

void Scene::Render() {
    RenderState state;
    state.wEye = camera->GetWEye();
    state.V = camera->V();
    state.P = camera->P();
    state.light = light.get();
    for (auto& obj : objects) obj->Draw(state);
}

void Scene::Animate(float tstart, float tend) {
    for (Animatable* animatable : animatables) animatable->Animate(tstart, tend);
}

void Scene::StartMovingCamera(){
    camera->StartMoving();
    for (Tire* tire : tires) tire->StartAcceleration();
}

void Scene::SwitchCameraLane(bool right){
    camera->SwitchLane(right);
}

void Scene::OnResize(){
    camera->OnResize();
    glViewport(0,0,windowWidth, windowHeight);
}

Scene::Scene(unsigned int& windowWidth, unsigned int& windowHeight) :
        windowWidth(windowWidth), windowHeight(windowHeight){
}

Scene::~Scene() = default;
