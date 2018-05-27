//
// Created by Bendi on 5/27/2018.
//

#ifndef BUTTERFLY_FLOWERMANAGER_HPP
#define BUTTERFLY_FLOWERMANAGER_HPP

#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

class FlowerManager{
private:

    class Flower;

    vector<unique_ptr<Flower>> flowers;

public:
    FlowerManager() noexcept ;

    void create();

    void draw();

    void addFlower(float x, float y);

    ~FlowerManager();
};

#endif //BUTTERFLY_FLOWERMANAGER_HPP
