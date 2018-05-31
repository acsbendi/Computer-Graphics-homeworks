//
// Created by Bendi on 5/30/2018.
//

#include <memory>
#include "intersectable.hpp"
#include "material.hpp"

using std::move;

Intersectable::Intersectable(unique_ptr<Material> material) : materials{}
{
    materials.push_back(move(material));
}

Intersectable::Intersectable() = default;

Intersectable::~Intersectable() = default;