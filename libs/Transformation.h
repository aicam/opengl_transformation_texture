//
// Created by root on 4/30/20.
//

#ifndef EP17_TEXTURES_TRANSFORMATION_H
#define EP17_TEXTURES_TRANSFORMATION_H


#include <glm/detail/type_mat.hpp>

class Transformation {
private:
    long WPressedTime, SPressedTime, APressedTime, DPressedTime, QPressedTime, EPressedTime;
public:
    void pressedKey(int keyID);
    glm::mat4 transform(glm::mat4 &transformation, float vertices[32]);
};


#endif //EP17_TEXTURES_TRANSFORMATION_H
