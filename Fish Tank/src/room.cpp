//
// Created by Bendi on 5/30/2018.
//

#include <memory>
#include "room.hpp"
#include "hit.hpp"
#include "wall.hpp"
#include "material.hpp"

using std::make_unique;
using std::move;

Room::Room(vec3 vertex1, vec3 vertex2, unique_ptr<Material>&& material1, unique_ptr<Material>&& material2) {
    walls.push_back(
            make_unique<Wall>(vec3(vertex1.x, vertex1.y, vertex2.z), vec3(vertex1.x, vertex2.y, vertex2.z), vertex2,
                              make_unique<Material>(*material1), make_unique<Material>(*material2)));
    walls.push_back(make_unique<Wall>(vec3(vertex2.x, vertex1.y, vertex2.z), vec3(vertex2.x, vertex2.y, vertex2.z),
                                      vec3(vertex2.x, vertex2.y, vertex1.z),
                                      make_unique<Material>(*material1), make_unique<Material>(*material2)));
    walls.push_back(make_unique<Wall>(vec3(vertex2.x, vertex2.y, vertex2.z), vec3(vertex1.x, vertex2.y, vertex2.z),
                                      vec3(vertex1.x, vertex2.y, vertex1.z),
                                      make_unique<Material>(*material1), make_unique<Material>(*material2)));
    walls.push_back(make_unique<Wall>(vec3(vertex1.x, vertex1.y, vertex2.z), vec3(vertex1.x, vertex2.y, vertex2.z),
                                      vec3(vertex1.x, vertex2.y, vertex1.z),
                                      make_unique<Material>(*material1), make_unique<Material>(*material2)));
    walls.push_back(make_unique<Wall>(vec3(vertex2.x, vertex1.y, vertex2.z), vec3(vertex1.x, vertex1.y, vertex2.z),
                                      vec3(vertex1.x, vertex1.y, vertex1.z),
                                      make_unique<Material>(*material1), make_unique<Material>(*material2)));
    walls.push_back(
            make_unique<Wall>(vertex1, vec3(vertex1.x, vertex2.y, vertex1.z), vec3(vertex2.x, vertex2.y, vertex1.z),
                              move(material1), move(material2)));
}

Room::Room(vec3 vertex1, vec3 vertex2, unique_ptr<Material>&& material) :
        Room{vertex1, vertex2, make_unique<Material>(*material), move(material)}
{}

Room::Room(vec3 vertex1, vec3 vertex2) :
        Room(vertex1, vertex2, make_unique<Material>(vec3(0.3, 0.2, 0.1) * 6, vec3(0.3, 0.2, 0.1), vec3(10, 10, 10), 100),
             make_unique<Material>(vec3(0.1, 0.2, 0.3) * 6, vec3(0.1, 0.2, 0.3), vec3(10, 10, 10), 100)) {
}

Hit Room::intersect(const Ray &ray) const {
    Hit bestHit{};
    for (const auto& wall : walls) {
        Hit hit = wall->intersect(ray); //  hit.t < 0 if no intersection
        if (hit.t > 0 && (bestHit.t < 0 || hit.t < bestHit.t)) bestHit = hit;
    }
    return bestHit;
}

Room::~Room() = default;