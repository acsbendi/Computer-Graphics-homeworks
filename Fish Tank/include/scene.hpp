//
// Created by Bendi on 5/30/2018.
//

#ifndef TEXTURE_TEST_SCENE_HPP
#define TEXTURE_TEST_SCENE_HPP

#include <memory>
#include <vector>
#include "utils.hpp"
#include "hit.hpp"
#include "ray.hpp"

using std::unique_ptr;
using std::vector;

class Intersectable;
class Light;
class Camera;
class FishTank;

class Scene {
    const unsigned int windowWidth;
    int startX, startY, endX, endY;
    vector<unique_ptr<Intersectable>> objects;
    vector<unique_ptr<Light>> lights;
    unique_ptr<Camera> camera;
    vec3 La;
    int MAX_DEPTH;

public:
    Scene(int startX, int startY, int endX, int endY, unsigned int windowWidth,
          unique_ptr<Camera> camera, unique_ptr<FishTank> fishTank);

    void build();

    void render(vec3 image[]);

    Hit firstIntersect(Ray ray);

    vec3 trace(Ray ray, int d = 0);

    vec3 directLight(const Hit &hit, const Ray &ray);

    ~Scene();
};

#endif //TEXTURE_TEST_SCENE_HPP
