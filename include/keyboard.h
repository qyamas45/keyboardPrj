#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>
#include "key.h"



class keyboard{ 
public:
    keyboard();
    ~keyboard();
    void Draw(Shader &shader);
    void pressKey(Alphabet key);
    void releaseKey(Alphabet key);
private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
    Key keys[26];

};
#endif