//
// Created by Bendi on 5/27/2018.
//

#include <cmath>
#include "petals.hpp"
#include "opengl.hpp"
#include "utils.hpp"
#include "camera.hpp"

void FlowerManager::Flower::Petals::CreateVertex() {
    vertexCoords = vector<float>(2 * N + 4);
    vertexColors = vector<float>(3 * N + 6);

    vertexCoords[0] = X;
    vertexCoords[1] = Y;

    for (int i = 1; i <= N; ++i) {
        auto f = static_cast<float>(i * M_PI * 2 / (N - 5));
        vertexCoords[2 * i] = X + cosf(f) * (R + (cosf(petalCount * f / 2)) * (cosf(petalCount * f / 2)) / 2);
        vertexCoords[2 * i + 1] = Y + sinf(f) * (R + (cosf(petalCount * f / 2)) * cosf(petalCount * f / 2) / 2);
    }

    for (int i = 0; i < N; ++i) {
        vertexColors[3 * i] = 0.9098f;
        vertexColors[3 * i + 1] = 0.1059f;
        vertexColors[3 * i + 2] = 0.1678f;
    }

}

FlowerManager::Flower::Petals::Petals(float r, float x, float y) : R(r), X(x), Y(y), petalCount(getNextFibonacci()) {

}

void FlowerManager::Flower::Petals::create() {
    CreateVertex();
    glGenVertexArrays(1, &vao);    // create 1 vertex array object
    glBindVertexArray(vao);        // make it active

    unsigned int vbo[2];        // vertex buffer objects
    glGenBuffers(2, &vbo[0]);    // Generate 4 vertex buffer objects

    // vertex coordinates: vbo[0] -> Attrib Array 0 -> vertexPosition of the vertex shader
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // make it active, it is an array
    glBufferData(GL_ARRAY_BUFFER,      // copy to the GPU
                 sizeof(float) * vertexCoords.size(), // number of the vbo in bytes
                 vertexCoords.data(),           // address of the data array on the CPU
                 GL_STATIC_DRAW);       // copy to that part of the memory which is not modified
    // Map Attribute Array 0 to the current bound vertex buffer (vbo[0])
    glEnableVertexAttribArray(0);
    // Data organization of Attribute Array 0
    glVertexAttribPointer(0,            // Attribute Array 0
                          2, GL_FLOAT,  // components/attribute, component type
                          GL_FALSE,        // not in fixed point format, do not normalized
                          0, nullptr);     // stride and offset: it is tightly packed

    // vertex colors: vbo[1] -> Attrib Array 1 -> vertexColor of the vertex shader
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // make it active, it is an array
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexColors.size(), vertexColors.data(),
                 GL_STATIC_DRAW);    // copy to the GPU
    // Map Attribute Array 1 to the current bound vertex buffer (vbo[1])
    glEnableVertexAttribArray(1);  // Vertex position
    // Data organization of Attribute Array 1
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0,
                          nullptr); // Attribute Array 1, components/attribute, component type, normalize?, tightly packed
}

void FlowerManager::Flower::Petals::draw() {
    mat4 MVPTransform = mat4(1, 0, 0, 0,
                             0, 1, 0, 0,
                             0, 0, 1, 0,
                             0, 0, 0, 1) * camera.V() * camera.P();

    // set GPU uniform matrix variable MVP with the content of CPU variable MVPTransform
    int location = glGetUniformLocation(shaderProgram, "MVP");
    if (location >= 0)
        glUniformMatrix4fv(location, 1, GL_TRUE,
                           static_cast<const float *>(MVPTransform)); // set uniform variable MVP to the MVPTransform
    else printf("uniform MVP cannot be set\n");

    glBindVertexArray(vao);    // make the vao and its vbos active playing the role of the data source
    glDrawArrays(GL_TRIANGLE_FAN, 0, N);    // draw a single triangle with vertices defined in vao
}

unsigned int FlowerManager::Flower::Petals::getNextFibonacci() {
    static unsigned int secondToLast = 1;
    static unsigned int last = 2;
    unsigned int current = secondToLast + last;
    secondToLast = last;
    last = current;
    return current;
}
