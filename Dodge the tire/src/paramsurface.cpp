//
// Created by Bendi on 5/26/2018.
//

#include <cstdlib>
#include <vector>
#include "opengl.hpp"
#include "utils.hpp"
#include "paramsurface.hpp"

using std::vector;

ParamSurface::ParamSurface(bool holes) : Geometry(GL_TRIANGLES), holes(holes) {
    srand(3846935435);
}

SurfacePointData ParamSurface::GenSurfacePointData(float u, float v) const {
    return SurfacePointData();
}

void ParamSurface::Create(int N, int M) {
    unsigned int vbo;
    glGenBuffers(1, &vbo); // Generate 1 vertex buffer object
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    nVertices = N * M * 3;
    vector<VertexData> vtxData;   // vertices on the CPU
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (!holes || rand() % 3 != 0) {
                nVertices += 3;
                vtxData.push_back(GenVertexData((float) i / N, (float) j / M));
                vtxData.push_back(GenVertexData((float) (i + 1) / N, (float) j / M));
                vtxData.push_back(GenVertexData((float) i / N, (float) (j + 1) / M));
            }
            vtxData.push_back(GenVertexData((float) (i + 1) / N, (float) j / M));
            vtxData.push_back(GenVertexData((float) (i + 1) / N, (float) (j + 1) / M));
            vtxData.push_back(GenVertexData((float) i / N, (float) (j + 1) / M));
        }
    }
    glBufferData(GL_ARRAY_BUFFER, nVertices * sizeof(VertexData), &vtxData[0], GL_STATIC_DRAW);
    // Enable the vertex attribute arrays
    glEnableVertexAttribArray(0);  // attribute array 0 = POSITION
    glEnableVertexAttribArray(1);  // attribute array 1 = NORMAL
    glEnableVertexAttribArray(2);  // attribute array 2 = TEXCOORD0
    // attribute array, components/attribute, component type, normalize?, stride, offset
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData),
                          static_cast<void *>(offsetof(VertexData, position)));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void *) offsetof(VertexData, normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void *) offsetof(VertexData, texcoord));
}