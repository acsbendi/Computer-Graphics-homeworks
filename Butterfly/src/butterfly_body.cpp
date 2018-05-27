//
// Created by Bendi on 5/27/2018.
//

#include "butterfly_body.hpp"
#include "catmullrom.hpp"
#include "opengl.hpp"
#include "physics.hpp"
#include "camera.hpp"

Butterfly::Body::Body(vec2 headPosition) : velocity(0.0f, 0.0f), position(0.0f, 0.0f) {
    animate(0);

    CatmullRom catmullRom;

    vec4 controlPoints[]{vec4(0.0f, 0.55f), vec4(0.05f, 0.3f),
                         vec4(0.0f, 0.0f), vec4(-0.05f, 0.3f), vec4(0.0f, 0.55f)};

    mat4 translationMatrix(1, 0, 0, 0,
                           0, 1, 0, 0,
                           0, 0, 1, 0,
                           -headPosition.x, -headPosition.y, 0, 1);

    for (int i = 0; i < 5; ++i) {
        catmullRom.AddControlPoint(controlPoints[i] * translationMatrix, static_cast<float>(i) / 5);
    }

    vertices[0] = vec2{vec4{0.0f, 0.3f} * translationMatrix};
    colors[0] = middleColor;

    for (int i = 1; i < N; ++i) {
        vec4 r = catmullRom.r(static_cast<float>(i - 1) / (N - 2));
        vertices[i].x = r.v[0];
        vertices[i].y = r.v[1];

        colors[i] = color;
    }

    vertices[N - 1] = vertices[2];
}

void Butterfly::Body::create() {
    glGenVertexArrays(1, &vao);    // create 1 vertex array object
    glBindVertexArray(vao);        // make it active

    glGenBuffers(2, vbo);    // Generate 1 vertex buffer objects

    // vertex coordinates: vbo[0] -> Attrib Array 0 -> vertexPosition of the vertex shader
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // make it active, it is an array
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices,
                 GL_STATIC_DRAW);       // copy to that part of the memory which will be modified
    // Map Attribute Array 0 to the current bound vertex buffer (vbo[0])
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);     // stride and offset: it is tightly packed

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // make it active, it is an array
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors,
                 GL_STATIC_DRAW);       // copy to that part of the memory which is not modified
    // Map Attribute Array 0 to the current bound vertex buffer (vbo[0])
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);     // stride and offset: it is tightly packed
}

void Butterfly::Body::animate(float dt) {
    vec2 butAccel = F(position, velocity) / m;
    if (butAccel.length() == 0.0f)
        velocity = vec2{0.0f, 0.0f};
    velocity += butAccel * dt;
    position += velocity * dt;
}

void Butterfly::Body::draw() {
    static vec3 lastVelocity = vec3{0.0f, 1.0f};
    if (velocity.length() != 0.0f)
        lastVelocity = vec3{velocity};
    vec3 j = (velocity.length() != 0 ? vec3{velocity} / velocity.length() : lastVelocity / lastVelocity.length());
    vec3 i = ((j.cross(Fbut(position, m))).length() != 0 ? j.cross(Fbut(position, m)) /
                                                           (j.cross(Fbut(position, m))).length() : j.cross(
            Fbut(position, m)));
    vec3 k = i.cross(j);

    mat4 frenet(i.x, i.y, i.z, 0,
                j.x, j.y, j.z, 0,
                k.x, k.y, k.z, 0,
                position.x, position.y, 0, 1);

    mat4 MVPTransform = mat4(2.0f, 0, 0, 0,
                             0, 2.0, 0, 0,
                             0, 0, 1, 0,
                             0, 0, 0, 1) * frenet * camera.V() * camera.P();

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);    // make the vao and its vbos active playing the role of the data source
    // set GPU uniform matrix variable MVP with the content of CPU variable MVPTransform
    int location = glGetUniformLocation(shaderProgram, "MVP");
    if (location >= 0)
        glUniformMatrix4fv(location, 1, GL_TRUE, static_cast<float *>(MVPTransform)); // set uniform variable MVP to the MVPTransform
    else printf("uniform MVP cannot be set\n");

    glDrawArrays(GL_TRIANGLE_FAN, 0, N);
}