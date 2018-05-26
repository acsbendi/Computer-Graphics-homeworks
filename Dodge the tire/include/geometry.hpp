//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_GEOMETRY_HPP
#define DODGE_THE_TIRE_GEOMETRY_HPP

//---------------------------
class Geometry {
//---------------------------
    unsigned int vao, type;        // vertex array object
protected:
    int nVertices;
public:
    explicit Geometry(unsigned int _type);

    void Draw();

    virtual ~Geometry();
};

#endif //DODGE_THE_TIRE_GEOMETRY_HPP
