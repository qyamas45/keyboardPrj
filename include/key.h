#ifndef KEY_H
#define KEY_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>
#include "character.h"

class Key
{
public:
    Letter letter;
    Key();
    ~Key();

    glm::vec3 position;
    glm::vec3 rotationAxis;
    float rotationAngle;
    glm::vec3 scale;
    char label;

    void Draw(Shader &shader, glm::mat4 view, glm::mat4 projection);
    void press();
    void release();

private:
    unsigned int VAO3D, VBO3D;
    unsigned int VAO, VBO, EBO;
    void setupMesh();
};
#endif