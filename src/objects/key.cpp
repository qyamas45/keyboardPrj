#include "key.h"


Key::Key()
{

}

Key::~Key()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
void Key::Draw(Shader &shader)
{

}

void Key::setupMesh()
{

}