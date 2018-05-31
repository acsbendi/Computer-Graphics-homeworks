//
// Created by Bendi on 5/30/2018.
//

#ifndef FISH_TANK_INTERSECTABLE_HPP
#define FISH_TANK_INTERSECTABLE_HPP

#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

class Material;
class Hit;
class Ray;

class Intersectable {
protected:
    vector<unique_ptr<Material>> materials;

    explicit Intersectable();

    explicit Intersectable(unique_ptr<Material> material);
public:
    virtual Hit intersect(const Ray& ray) const = 0;

    virtual ~Intersectable();
};

#endif //FISH_TANK_INTERSECTABLE_HPP
