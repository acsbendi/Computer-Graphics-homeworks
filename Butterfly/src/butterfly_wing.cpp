//
// Created by Bendi on 5/27/2018.
//

#include <vector>
#include <memory>
#include "camera.hpp"
#include "physics.hpp"
#include "butterfly_wing.hpp"
#include "catmullrom.hpp"
#include "opengl.hpp"

using std::vector;
using std::unique_ptr;
using std::make_unique;

void Butterfly::Wing::createTexture(){

    class Shape{
    private:
        vec3 color;

    protected:
        explicit Shape(const vec3& color) : color(color){}

    public:
        virtual vec3 getColorFor(const vec2& point) const{
            if(isInside(point))
                return color;
            else
                return vec3(0.0f,0.0f,0.0f);
        }
        virtual bool isInside(const vec2& point) const = 0;
        virtual ~Shape() = default;
    };


    class Ellipse : public Shape{
    private:
        const vec2 focuses[2];
        const float r;

    public:
        Ellipse(const vec2& focus1, const vec2& focus2, float r, const vec3& color) : Shape(color), r(r), focuses{focus1,focus2} {

        }

        bool isInside(const vec2& point) const override{
            return point.distance(focuses[0]) + point.distance(focuses[1]) < r;
        }
    };

    class ParabolaX : public Shape{
    private:
        const vec2 focus;
        const float x;

    public:
        ParabolaX(const vec2& focus, float x, const vec3& color) : Shape(color), x(x), focus(focus) {
        }

        bool isInside(const vec2& point) const override{
            return point.distance(focus) < fabsf(point.x - x);
        }
    };

    vector<unique_ptr<Shape>> shapes;
    shapes.push_back(make_unique<ParabolaX>(vec2(100,100),35,vec3(0.9531f, 0.2539f, 0.9297f)));
    shapes.push_back(make_unique<ParabolaX>(vec2(-12,100),75,vec3(0.9531f, 0.2539f, 0.9297f)));
    shapes.push_back(make_unique<Ellipse>(vec2(66,32),vec2(76,16),34,vec3(0.9843f, 0.5195f, 0.9688f)));
    shapes.push_back(make_unique<Ellipse>(vec2(32,32),vec2(22,16),34,vec3(0.9843f, 0.5195f, 0.9688f)));
    shapes.push_back(make_unique<Ellipse>(vec2(24,102),vec2(18,94),24,vec3(0.9531f, 0.8711f, 0.2539f)));
    shapes.push_back(make_unique<Ellipse>(vec2(84,102),vec2(78,94),24,vec3(0.9531f, 0.8711f, 0.2539f)));
    //shapes.push_back(make_unique<Ellipse>(vec2(47,102),vec2(47,20),85,vec3(0.9531f, 0.8711f, 0.2539f)));


    const vec3 background{0.2578f, 0.8477f, 0.9531f};

    int width = 128, height = 128;
    vec3 image[width * height];
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            vec2 current(static_cast<float >(x), static_cast<float>(y));
            for(auto& shape : shapes)
                if(shape->getColorFor(current).length() > 0.001f)
                    image[y * width + x] = shape->getColorFor(current);
            if(image[y * width + x].length() < 0.001f)
                image[y * width + x] = background;
        }
    }

    // Create objects by setting up their vertex data on the GPU
    glGenTextures(1, &textureId);  				// id generation
    glBindTexture(GL_TEXTURE_2D, textureId);    // binding

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_FLOAT, image); // To GPU

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // sampling
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Butterfly::Wing::Wing(bool reverse, vec2 headPosition) : reverse{reverse}, velocity{0.0f,0.0f} , position(0.0f,0.0f) {
    animate(0,0);

    CatmullRom catmullRom;

    mat4 reverseTransform( -1 , 0, 0, 0,
                           0, 1, 0, 0,
                           0, 0, 1, 0,
                           0, 0, 0, 1);

    mat4 translationMatrix( 1 , 0, 0, 0,
                            0, 1, 0, 0,
                            0, 0, 1, 0,
                            -headPosition.x, -headPosition.y, 0, 1);

    vec4 controlPoints[]{vec4(0.0f,0.55f),vec4(0.1f,0.633f), vec4(0.2f,0.66f), vec4(0.3f,0.6f), vec4(0.3f,0.5f),vec4(0.26f,0.4f),
                         vec4(0.23f,0.3f),vec4(0.285f,0.2f), vec4(0.28f,0.1f),vec4(0.22f,0.0f), vec4(0.15f,-0.04f),vec4(0.08f,-0.03f),vec4(0.0f,0.0f) };

    catmullRom.AddControlPoint(reverse ? controlPoints[0]*reverseTransform*translationMatrix : controlPoints[0]*translationMatrix,0.0f);
    catmullRom.AddControlPoint(reverse ? controlPoints[1]*reverseTransform*translationMatrix : controlPoints[1]*translationMatrix,0.09f);
    catmullRom.AddControlPoint(reverse ? controlPoints[2]*reverseTransform*translationMatrix : controlPoints[2]*translationMatrix,0.18f);
    catmullRom.AddControlPoint(reverse ? controlPoints[3]*reverseTransform*translationMatrix : controlPoints[3]*translationMatrix,0.26f);
    catmullRom.AddControlPoint(reverse ? controlPoints[4]*reverseTransform*translationMatrix : controlPoints[4]*translationMatrix,0.34f);
    catmullRom.AddControlPoint(reverse ? controlPoints[5]*reverseTransform*translationMatrix : controlPoints[5]*translationMatrix,0.43f);
    catmullRom.AddControlPoint(reverse ? controlPoints[6]*reverseTransform*translationMatrix : controlPoints[6]*translationMatrix,0.53f);
    catmullRom.AddControlPoint(reverse ? controlPoints[7]*reverseTransform*translationMatrix : controlPoints[7]*translationMatrix,0.62f);
    catmullRom.AddControlPoint(reverse ? controlPoints[8]*reverseTransform*translationMatrix : controlPoints[8]*translationMatrix,0.71f);
    catmullRom.AddControlPoint(reverse ? controlPoints[9]*reverseTransform*translationMatrix : controlPoints[9]*translationMatrix,0.79f);
    catmullRom.AddControlPoint(reverse ? controlPoints[10]*reverseTransform*translationMatrix : controlPoints[10]*translationMatrix,0.9f);
    catmullRom.AddControlPoint(reverse ? controlPoints[11]*reverseTransform*translationMatrix : controlPoints[11]*translationMatrix,0.95f);
    catmullRom.AddControlPoint(reverse ? controlPoints[12]*reverseTransform*translationMatrix : controlPoints[12]*translationMatrix,1.0f);

    vec4 startPoint = vec4(0.0f,0.3f) * translationMatrix;

    vertices[0] = vec2{startPoint.v[0],startPoint.v[1]};
    vertices[1] = vec2{startPoint.v[2],startPoint.v[3]};

    for (int i = 1; i < N; ++i) {
        vec4 r = catmullRom.r(static_cast<float>(i-1)/(N-2));
        vertices[i].x = r.v[0];
        vertices[i].y = r.v[1];
    }


    uvs[0] = vec2(0, 0);
    uvs[1] = vec2(1, 0);
    uvs[2] = vec2(1, 1);
    uvs[3] = vec2(0, 1);
}

void Butterfly::Wing::create( ) {
    glGenVertexArrays(1, &vao);	// create 1 vertex array object
    glBindVertexArray(vao);		// make it active

    glGenBuffers(2, vbo);	// Generate 1 vertex buffer objects

    // vertex coordinates: vbo[0] -> Attrib Array 0 -> vertexPosition of the vertex shader
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); // make it active, it is an array
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	   // copy to that part of the memory which will be modified
    // Map Attribute Array 0 to the current bound vertex buffer (vbo[0])
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);     // stride and offset: it is tightly packed

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]); // make it active, it is an array
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);	   // copy to that part of the memory which is not modified
    // Map Attribute Array 0 to the current bound vertex buffer (vbo[0])
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);     // stride and offset: it is tightly packed

    createTexture();

}

void Butterfly::Wing::animate(float dt, float time){
    vec2 butAccel = F(position, velocity)/m;
    if(butAccel.length() == 0.0f)
        velocity = vec2{0.0f,0.0f};
    velocity += butAccel * dt;
    position += velocity * dt;

    phi = time;
}

void Butterfly::Wing::draw() {
    static vec3 lastVelocity = vec3{0.0f,1.0f};
    if(velocity.length() != 0.0f)
        lastVelocity = vec3{velocity};
    vec3 j = (velocity.length() != 0 ? vec3{velocity}/velocity.length() : lastVelocity/lastVelocity.length());
    vec3 i = ((j.cross(Fbut(position,m))).length() != 0 ? j.cross(Fbut(position,m))/
                                                          (j.cross(Fbut(position,m))).length() : j.cross(Fbut(position,m)));
    vec3 k = i.cross(j);

    mat4 frenet{ i.x, i.y, i.z, 0,
                 j.x, j.y, j.z, 0,
                 k.x, k.y, k.z, 0,
                 position.x, position.y,  0, 1};

    mat4 MVPTransform =   mat4( (2.0f/1.4f) * ( cosf(8*phi)* cosf(8*phi) + 0.4f) , 0, 0, 0,
                                0, 2.0, 0, 0,
                                0,            0,          1, 0,
                                0,            0,          0, 1) * frenet * camera.V() * camera.P();

    glUseProgram(textureShaderProgram);
    glBindVertexArray(vao);	// make the vao and its vbos active playing the role of the data source

    // set GPU uniform matrix variable MVP with the content of CPU variable MVPTransform
    int location = glGetUniformLocation(textureShaderProgram, "MVP");
    if (location >= 0) glUniformMatrix4fv(location, 1, GL_TRUE, static_cast<float *>(MVPTransform)); // set uniform variable MVP to the MVPTransform
    else printf("uniform MVP cannot be set\n");

    location = glGetUniformLocation(textureShaderProgram, "textureUnit");
    if (location >= 0) {
        glUniform1i(location, 0);		// texture sampling unit is TEXTURE0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureId);	// connect the texture to the sampler
    }
    glDrawArrays(GL_TRIANGLE_FAN, 0, N);	// draw two triangles forming a quad
}