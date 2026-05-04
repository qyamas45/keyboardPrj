#ifndef KEY_H
#define KEY_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>
#include "character.h"
#include <iostream>
#include <GLFW/glfw3.h>

 
class Key
{
public:
    Letter letter;
    int GLFWKey; 
    Key(std::string);
    ~Key();
    glm::vec3 position;
    glm::vec3 rotationAxis;
    float rotationAngle;
    glm::vec3 scale;
    std::string label;
    void setKeyType(std::string);
    void Draw(Shader&, glm::mat4, glm::mat4);
    void press(int, int);
    static void keyCallBack(GLFWwindow*, int, int, int, int);
    void release();
    void offSetSize(float&);
    float getWidth() const;
    float adjustedSize = 0.0f; 
private:
    unsigned int VAO3D, VBO3D;
    unsigned int VAO, VBO, EBO;
    void setupMesh();
};
#endif