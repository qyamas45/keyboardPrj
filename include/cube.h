#ifndef CUBE_H
#define CUBE_H
 
#include <string>
#include <map>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>
#include <glm/gtc/type_ptr.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H
 

class Cube
{
public:
    Cube();
    ~Cube();
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