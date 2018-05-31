//
// Created by Bendi on 5/30/2018.
//

#ifndef FISH_TANK_ROOM_HPP
#define FISH_TANK_ROOM_HPP

#include <vector>
#include <memory>
#include "intersectable.hpp"
#include "utils.hpp"

using std::unique_ptr;
using std::vector;

class Wall;

class Room : public virtual Intersectable {
private:
    vector<unique_ptr<Wall>> walls;

protected:
    Room(vec3 vertex1, vec3 vertex2, unique_ptr<Material>&& material1, unique_ptr<Material>&& material2);

    Room(vec3 vertex1, vec3 vertex2, unique_ptr<Material>&& material);

public:
    explicit Room(vec3 vertex1 = vec3{-2.5f,2.5f,5.2f}, vec3 vertex2 = vec3{2.5f,-2.5f,-5.2f});

    Hit intersect(const Ray& ray) const override ;

    ~Room() override;
};


#endif //FISH_TANK_ROOM_HPP
