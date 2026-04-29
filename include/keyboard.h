#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>
#include "key.h"

enum class keyboardKey{
    A = 0, B, C, D, E, F, G, H, I, J, K, 
    L, M, N, O, P, Q, R, S, T, U, V, W, 
    X, Y, Z, ENTER, SPACE, BACKSPACE, SHIFT, CTRL, ALT
        
};


class keyboard{ 
public:
    keyboard();
    ~keyboard();
    void Draw(Shader &shader);
    void pressKey(keyboardKey key);
    void releaseKey(keyboardKey key);
private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
    Key keys[26];

};
#endif