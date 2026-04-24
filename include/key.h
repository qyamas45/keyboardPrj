#ifndef KEY_H
#define KEY_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>
#include "character.h"

enum class Alphabet{
    A = 0, B, C, D, E, F, G, H, I, J, K, 
    L, M, N, O, P, Q, R, S, T, U, V, W, 
    X, Y, Z
};

class Key
{
public:
    Key();
    ~Key();

    glm::vec3 position;
    glm::vec3 rotationAxis;
    float rotationAngle;
    glm::vec3 scale;
    char label;

    void Draw(Shader &shader, Letter &letter, glm::mat4 view, glm::mat4 projection);
    void press();
    void release();

private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
};
#endif