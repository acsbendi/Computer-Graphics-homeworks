//
// Created by Bendi on 5/30/2018.
//

#include <memory>
#include "scene.hpp"
#include "camera.hpp"
#include "goldenthing.hpp"
#include "room.hpp"
#include "material.hpp"
#include "fishtank.hpp"
#include "light.hpp"

using std::make_unique;

Scene::Scene(int startX, int startY, int endX, int endY, unsigned int windowWidth,
             unique_ptr<Camera> camera, unique_ptr<FishTank> fishTank) :
        startX(startX), startY(startY), endX(endX), endY(endY), windowWidth(windowWidth), camera(move(camera)), La{0.1f, 0.1f, 0.1f}
{
    this->camera->set(endX - startX,endY - startY);
    objects.push_back(move(fishTank));
}

void Scene::build() {
    lights.push_back(make_unique<Light>(vec3(-1, -1, -1), vec3(3, 3, 3)));
    lights.push_back(make_unique<Light>(vec3(1, 1, 1), vec3(1, 4.5f, 4.0f)));

    objects.push_back(make_unique<GoldenThing>(vec3(-0.4f, -0.4f, -1), 1.5f));
    objects.push_back(make_unique<Room>());
}

void Scene::render( vec3 image[] ) {
#pragma omp parallel for
    for (int Y = startY; Y < endY; Y++) {
        for (int X = startX; X < endX; X++) {
            image[Y * windowWidth + X] = trace(camera->getRay(X - startX, Y - startY));
        }
    }
}

Hit Scene::firstIntersect(Ray ray) {
    Hit bestHit{};
    for (auto& object : objects) {
        Hit hit = object->intersect(ray); //  hit.t < 0 if no intersection
        if (hit.t > 0 && (bestHit.t < 0 || hit.t < bestHit.t))  bestHit = hit;
    }
    return bestHit;
}

vec3 Scene::trace(Ray ray, int d) {
    if(d > MAX_DEPTH)
        return La;
    Hit hit = firstIntersect(ray);
    if(hit.t < 0) return La; // nothing
    vec3 outRad(0, 0, 0);
    if(hit.material->rough) outRad  = directLight(hit,ray);


    if(hit.material->reflective){
        vec3 reflectionDir = reflect(ray.dir,hit.normal);
        Ray reflectRay(hit.position + hit.normal * 0.001f, reflectionDir, ray.out);
        outRad += trace(reflectRay, d+1)*hit.material->fresnelApprox(ray.dir,hit.normal);
    }

    if(hit.material->refractive) {
        float N = (ray.out) ? camera->getSourceRefractiveIndex().x : 1/camera->getSourceRefractiveIndex().x;
        vec3 refractionDir = refract(ray.dir,hit.normal,N);
        if (refractionDir.length() > 0) {
            Ray refractRay(hit.position - hit.normal * 0.001f, refractionDir, !ray.out);
            vec3 fresnel = hit.material->fresnelApprox(ray.dir,hit.normal);
            vec3 traced = trace(refractRay);
            outRad += traced*(vec3(1,1,1) - fresnel);
        }
    }

    return outRad;
}

vec3 Scene::directLight(const Hit& hit, const Ray& ray){
    vec3 outRadiance = hit.material->ka * La;
    for (auto& light : lights) {
        Ray shadowRay(hit.position + hit.normal * 0.00001f, light->getPosition() - hit.position, false);
        Hit shadowHit = firstIntersect(shadowRay);
        if(shadowHit.t > (hit.position - (light->getPosition() - (hit.position + hit.normal * 0.00001f ))).length() || shadowHit.t < 0) {
            outRadiance += hit.material->shade(hit.normal, -ray.dir,  light->getPosition() - hit.position, light->getLe(hit.position));
        }
    }
    return outRadiance;
}

Scene::~Scene() = default;