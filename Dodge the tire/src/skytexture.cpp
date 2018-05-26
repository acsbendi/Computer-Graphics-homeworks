//
// Created by Bendi on 5/26/2018.
//

#include "texture.hpp"
#include "skytexture.hpp"
#include "utils.hpp"

inline void SkyTexture::FillCloudCircle(unsigned int x, unsigned int y, float probability, Direction direction){
    if(probability < 0)
        return;

    FillCircle(x,y,cloudColors,cloudR);

    int nextDistance = static_cast<int>(cloudR * nextDistanceFactor);

    if(x - nextDistance >= 0 && direction != right && rand() % static_cast<int>(1/probability) == 0){
        FillCloudCircle(x - nextDistance, y, probability * probabilityDecreaseFactor, left);
    }
    if(x + nextDistance <= width - 1 && direction != left && rand() % static_cast<int>(1/probability) == 0){
        FillCloudCircle(x + nextDistance, y, probability * probabilityDecreaseFactor, right);
    }
    if(y - nextDistance >= 0 && direction != down && rand() % static_cast<int>(1/probability) == 0){
        FillCloudCircle(x, y - nextDistance, probability * probabilityDecreaseFactor, up);
    }
    if(y + nextDistance <= height - 1 && direction != up && rand() % static_cast<int>(1/probability) == 0){
        FillCloudCircle(x, y + nextDistance, probability * probabilityDecreaseFactor, down);
    }
}

void SkyTexture::FillCircle(unsigned int x, unsigned int y, const vec3 colorArray[6], int R){
    int xStart = x - R < 0 ? 0 : x - R;
    int yStart = y - R < 0 ? 0 : y - R;
    int xEnd = x + R > width - 1 ? width - 1 : x + R;
    int yEnd = y + R > height - 1 ? height - 1 : y + R;

    for(int i = xStart; i <= xEnd; ++i)
        for(int j = yStart; j <= yEnd; ++j){
            int distance2 = (i - x)*(i - x) + (j - y)*(j - y);
            if(distance2 < (static_cast<float>(R)*3/10)*(static_cast<float>(R)*3/10)){
                if(image[j * width + i].Lightness() < colorArray[0].Lightness())
                    image[j * width + i] = colorArray[0];
            } else if(distance2 < (static_cast<float>(R)*4.5f/10)*(static_cast<float>(R)*4.5f/10)){
                if(image[j * width + i].Lightness() < colorArray[1].Lightness())
                    image[j * width + i] = colorArray[1];
            }else if(distance2 < (static_cast<float>(R)*5.5f/10)*(static_cast<float>(R)*5.5f/10)){
                if(image[j * width + i].Lightness() < colorArray[2].Lightness())
                    image[j * width + i] = colorArray[2];
            }else if(distance2 < (static_cast<float>(R)*7.0f/10)*(static_cast<float>(R)*7.0f/10)){
                if(image[j * width + i].Lightness() < colorArray[3].Lightness())
                    image[j * width + i] = colorArray[3];
            }else if(distance2 < (static_cast<float>(R)*8.5f/10)*(static_cast<float>(R)*8.5f/10)){
                if(image[j * width + i].Lightness() < colorArray[4].Lightness())
                    image[j * width + i] = colorArray[4];
            }else if(distance2 < (static_cast<float>(R))*(static_cast<float>(R))) {
                if (image[j * width + i].Lightness() < colorArray[5].Lightness())
                    image[j * width + i] = colorArray[5];
            }
        }
}

SkyTexture::SkyTexture(const unsigned int width, const unsigned int height): Texture(width, height), width(width), height(height), cloudR(width/50), sunR(width/20) {
    srand(437482354);
    glBindTexture(GL_TEXTURE_2D, textureId);    // binding
    image = vector<vec3>(width * height);
    for (unsigned int x = 0; x < width; x++)
        for (unsigned int y = 0; y < height; y++)
            image[y * width + x] = blue;

    FillCloudCircle(width / 4, height / 4, 1, any);
    FillCloudCircle(2 * width / 4, height / 4, 1, any);
    FillCloudCircle(width / 4, 2 * height / 4, 1, any);
    probabilityDecreaseFactor = 0.87f;
    FillCloudCircle(2 * width / 4, 2 * height / 4, 1, any);

    FillCircle(5 * width / 13, 2 * height / 9, sunColors, sunR);

    probabilityDecreaseFactor = 0.85f;
    FillCloudCircle(3 * width / 4, 3 * height / 4, 1, any);
    probabilityDecreaseFactor = 0.5f;
    FillCloudCircle(2 * width / 4, 3 * height / 4, 1, any);
    FillCloudCircle(3 * width / 4, 2 * height / 4, 1, any);
    FillCloudCircle(3 * width / 4,  height / 4, 1, any);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, &image[0]); //Texture->OpenGL

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}