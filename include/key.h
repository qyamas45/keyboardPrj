#ifndef KEY_H
#define KEY_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>

class Key
{
public:
    Key();
    ~Key();

    glm::vec3 position;
    glm::vec3 rotationAxis;
    float rotationAngle;
    glm::vec3 scale;
    void Draw(Shader &shader);

private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
};
#endif