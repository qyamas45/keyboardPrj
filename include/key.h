#ifndef KEY_H
#define KEY_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>
#include "character.h"
#include <iostream>

class Key
{
public:
    Letter letter;
    Key(std::string);
    ~Key();
 

    glm::vec3 position;
    glm::vec3 rotationAxis;
    float rotationAngle;
    glm::vec3 scale;
    std::string label;
    void setKeyType();
    void Draw(Shader &shader, glm::mat4 view, glm::mat4 projection);
    void press(int, int);
    static void keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods);
    void release();
    void offSetSize(float&);
private:
    unsigned int VAO3D, VBO3D;
    unsigned int VAO, VBO, EBO;
    void setupMesh();
};
#endif