//
// Created by Bendi on 5/26/2018.
//

#ifndef DODGE_THE_TIRE_PHONGSHADER_HPP
#define DODGE_THE_TIRE_PHONGSHADER_HPP

#include "renderstate.hpp"
#include "shader.hpp"

//---------------------------
class PhongShader : public Shader {
//---------------------------
    const char * vertexSource = R"(
      #version 330
      precision highp float;

      uniform mat4  MVP, M, Minv; // MVP, Model, Model-inverse
      uniform vec4  wLiPos;       // light source direction
      uniform vec3  wEye;         // pos of eye

      layout(location = 0) in vec3  vtxPos;            // pos in modeling space
      layout(location = 1) in vec3  vtxNorm;          // normal in modeling space
      layout(location = 2) in vec2  vtxUV;

      out vec3 wNormal;         // normal in world space
      out vec3 wView;             // view in world space
      out vec3 wLight;          // light dir in world space
      out vec2 texcoord;

      void main() {
         gl_Position = vec4(vtxPos, 1) * MVP; // to NDC
         // vectors for radiance computation
         vec4 wPos = vec4(vtxPos, 1) * M;
         wLight = wLiPos.xyz * wPos.w - wPos.xyz * wLiPos.w;
         wView  = wEye * wPos.w - wPos.xyz;
         wNormal = (Minv * vec4(vtxNorm, 0)).xyz;
         if(dot(wNormal,wView) < 0)
            {wNormal = - wNormal;}

         texcoord = vtxUV;
      }
   )";

    // fragment shader in GLSL
    const char * fragmentSource = R"(
      #version 330
      precision highp float;

      uniform vec3 kd, ks, ka; // diffuse, specular, ambient ref
      uniform vec3 La, Le;     // ambient and point sources
      uniform float shine;     // shininess for specular ref
      uniform sampler2D diffuseTexture;

      in  vec3 wNormal;       // interpolated world sp normal
      in  vec3 wView;         // interpolated world sp view
      in  vec3 wLight;        // interpolated world sp illum dir
      in vec2 texcoord;
      out vec4 fragmentColor; // output goes to frame buffer

      void main() {
         vec3 N = normalize(wNormal);
         vec3 V = normalize(wView);
         vec3 L = normalize(wLight);
         vec3 H = normalize(L + V);
         float cost = max(dot(N,L), 0), cosd = max(dot(N,H), 0);
         vec3 texColor = texture(diffuseTexture, texcoord).rgb;

         // kd and ka are modulated by the texture
         vec3 color = ka * texColor * La + (kd * texColor * cost + ks * pow(cosd,shine)) * Le;
         fragmentColor = vec4(color, 1);
      }
   )";
public:
    PhongShader();

    void Bind(RenderState state) override;
};

#endif //DODGE_THE_TIRE_PHONGSHADER_HPP
