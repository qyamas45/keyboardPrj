#include "cube.h"

Cube::Cube() : position(0.0f), rotationAxis(0.0f, 1.0f, 0.0f), 
rotationAngle(0.0f), scale(1.0f), color(1.0f), useCustomColor(false)
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    rotationAngle = 0.0f;
    scale = glm::vec3(1.0f);
    
    setupMesh();
}
Cube::~Cube()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
void Cube::setColor(glm::vec3 color)
{
    // This function can be implemented to change the color of the cube by updating the vertex data or using a uniform in the shader.
    // For now, it's just a placeholder to indicate where color-setting logic would go.
    this->color = color;
    useCustomColor = true; // Indicate that a custom color should be used when drawing the cube

}
void Cube::setupMesh()
{
    float vertices[] = {
        //front face
       -0.5f, -0.5f, -0.5f,  0.75f, 0.75f, 0.75f,
        0.5f, -0.5f, -0.5f,  0.75f, 0.75f, 0.75f,
        0.5f,  0.5f, -0.5f,  0.75f, 0.75f, 0.75f,
        0.5f,  0.5f, -0.5f,  0.75f, 0.75f, 0.75f,
       -0.5f,  0.5f, -0.5f,  0.75f, 0.75f, 0.75f,
       -0.5f, -0.5f, -0.5f,  0.75f, 0.75f, 0.75f,

        //back
       -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
       -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

        //left
       -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

        //right
        0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
        //top
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
       -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,
       -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,
        //bottom
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
       -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
       -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)nullptr);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float) *3));
    glEnableVertexAttribArray(1);
 
}
void Cube::Draw(Shader& shader, glm::mat4 parentModel = glm::mat4(1.0f))
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotationAngle), rotationAxis);
    model = glm::scale(model, scale);
    shader.setMat4("model", parentModel * model);
    shader.setBool("useKeyColor", useCustomColor);
    if (useCustomColor)
        shader.setVec3("keyColor", color);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
