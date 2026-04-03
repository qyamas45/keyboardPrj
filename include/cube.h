#ifndef CUBE_H
#define CUBE_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>

class Cube{
    public:
        Cube();
        ~Cube();
        glm::vec3 position;
        glm::vec3 rotationAxis;
        float rotationAngle;
        glm::vec3 scale;

        void Draw(Shader& shader);  

    private:
        unsigned int VAO, VBO, EBO;
        void setupMesh();
};
#endif