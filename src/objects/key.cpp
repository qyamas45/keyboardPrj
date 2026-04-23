#include "key.h"


Key::Key() : position(0.0f), rotationAxis(0.0f, 1.0f, 0.0f), rotationAngle(0.0f), scale(1.0f)
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    rotationAngle = 0.0f;
    scale = glm::vec3(1.0f);

    setupMesh();
}

Key::~Key()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
void Key::press()
{

}
void Key::release()
{

}

void Key::Draw(Shader &shader)
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotationAngle), rotationAxis);
    model = glm::scale(model, scale);
    shader.setMat4("model", model);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void Key::setupMesh()
{
    float vertices[] = {
    //z: -0.3f
    -0.3f, -0.3f, 0.0f,  0.75f, 0.75f, 0.75f,  // 0 bottom-left
     0.3f, -0.3f, 0.0f,  0.75f, 0.75f, 0.75f,  // 1 bottom-right
     0.2f,  0.3f, 0.0f,  0.75f, 0.75f, 0.75f,  // 2 top-right
    -0.2f,  0.3f, 0.0f,  0.75f, 0.75f, 0.75f,  // 3 top-left

    //sideways (left)
    -0.3f, -0.3f,  0.0f,  0.75f, 0.75f, 0.75f,  // 4 bottom-right                     
    -0.3f, -0.3f, -0.5f,  0.75f, 0.75f, 0.75f,  // 5 bottom-left
    -0.2f,  0.3f,  0.0f,  0.75f, 0.75f, 0.75f,  // 6 top-right
    -0.2f,  0.3f, -0.5f,  0.75f, 0.75f, 0.75f,  // 7 top-left

    //sideways (right)
    0.3f, -0.3f,  0.0f,  0.75f, 0.75f, 0.75f,  // 8 bottom-right                     
    0.3f, -0.3f, -0.5f,  0.75f, 0.75f, 0.75f,  // 9 bottom-left
    0.2f,  0.3f,  0.0f,  0.75f, 0.75f, 0.75f,  // 10 top-right
    0.2f,  0.3f, -0.5f,  0.75f, 0.75f, 0.75f,   // 11 top-left

    //back
   -0.3f, -0.3f, -0.5f,  0.75f, 0.75f, 0.75f,  // 12 bottom-left
    0.3f, -0.3f, -0.5f,  0.75f, 0.75f, 0.75f,  // 13 bottom-right
    0.2f,  0.3f, -0.5f,  0.75f, 0.75f, 0.75f,  // 14 top-right
   -0.2f,  0.3f, -0.5f,  0.75f, 0.75f, 0.75f,  // 15 top-left

    //top
   -0.3f,  0.3f,  0.0f,  0.75f, 0.75f, 0.75f,  // 16 top-left
    0.3f,  0.3f,  0.0f,  0.75f, 0.75f, 0.75f,  // 17 top-right
    0.2f,  0.3f, -0.5f,  0.75f, 0.75f, 0.75f,   // 18 bottom-right
   -0.2f,  0.3f, -0.5f,  0.75f, 0.75f, 0.75f,   // 19 bottom-left

    //bottom
   -0.3f, -0.3f,  0.0f,  0.75f, 0.75f, 0.75f,  // 20 top-left
    0.3f, -0.3f,  0.0f,  0.75f, 0.75f, 0.75f,  // 21 top-right
    0.2f, -0.3f, -0.5f,  0.75f, 0.75f, 0.75f,   // 22 bottom-right
   -0.2f, -0.3f, -0.5f,  0.75f, 0.75f, 0.75f   // 23 bottom-left
};
unsigned int indices[] = {
    //front
    0, 1, 2,
    0, 2, 3,

    //sideways (left)
    4, 5, 6,
    5, 6, 7,

    //sideways (right)
    8, 9, 10,
    9, 10, 11,

    //back
    12, 13, 14,
    12, 14, 15,

    //top
    16, 17, 18,
    16, 18, 19,
    
    //bottom
    20, 21, 22,
    20, 22, 23
  
};

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

}