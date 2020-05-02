//
// Created by root on 4/30/20.
//
#include <time.h>
#include <glm/gtc/matrix_transform.hpp>
#include "Transformation.h"
#include "Debug.h"
#include <GLFW/glfw3.h>
#include <ctime>
//LPIC
void Transformation::pressedKey(int keyID) {
    switch (keyID) {
        case GLFW_KEY_S:
            SPressedTime = time(NULL);
            break;
        case GLFW_KEY_W:
            WPressedTime = time(NULL);
            break;
        case GLFW_KEY_A:
            APressedTime = time(NULL);
            break;
        case GLFW_KEY_D:
            DPressedTime = time(NULL);
            break;
        case GLFW_KEY_Q:
            QPressedTime = time(NULL);
            break;
        case GLFW_KEY_E:
            EPressedTime = time(NULL);
            break;
    }
}

glm::mat4 Transformation::transform(glm::mat4 &transformation, float vertices[32]) {
    srand((unsigned) time(NULL));
    time_t now = time(NULL);
    if (now - SPressedTime < 3)
        transformation = glm::scale(transformation, glm::vec3(1.0, 0.999, 1.0));
    if (now - WPressedTime < 3)
        transformation = glm::scale(transformation, glm::vec3(1.0, 1.001, 1.0));
    if (now - APressedTime < 3)
        transformation = glm::scale(transformation, glm::vec3(0.999, 1.0, 1.0));
    if (now - DPressedTime < 3)
        transformation = glm::scale(transformation, glm::vec3(1.001, 1.0, 1.0));
    if (now - QPressedTime < 3) {
        for (int i = 0; i < 4; i++){
            vertices[8*i + 3] = ((float) rand() / (RAND_MAX)) + 1;
            vertices[8*i + 4] = ((float) rand() / (RAND_MAX)) + 1;
            vertices[8*i + 5] = ((float) rand() / (RAND_MAX)) + 1;
        }
        transformation = glm::rotate(transformation, 0.01f, glm::vec3(0.0, 0.0, 1.0));
    }
    if (now - EPressedTime < 3) {
        for (int i = 0; i < 4; i++){
            vertices[8*i + 3] = ((float) rand() / (RAND_MAX)) + 1;
            vertices[8*i + 4] = ((float) rand() / (RAND_MAX)) + 1;
            vertices[8*i + 5] = ((float) rand() / (RAND_MAX)) + 1;
        }
        transformation = glm::rotate(transformation, -0.01f, glm::vec3(0.0, 0.0, 1.0));
    }
    return transformation;
}
