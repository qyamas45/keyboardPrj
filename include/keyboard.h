#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <vector>
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>
#include "key.h"

enum class keyboardKey{
    ESCAPE, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    GRAVE, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO, MINUS, EQUAL,
    BACKSPACE, TAB, Q, W, E, R, T, Y, U, I, O, P, BRACKL, BRACKR, PIPE,
    CAPSLOCK, A, S, D, F, G, H, J, K, L, SEMICOLON, APOSTROPHE, ENTER,
    LEFTSHIFT, Z, X, C, V, B, N, M, COMMA, PERIOD, SLASH, RIGHTSHIFT,
    LEFTCTRL, LEFTALT, SPACE, RIGHTALT, RIGHTCTRL
        
};

class keyboard{ 
public:
    keyboard();
    ~keyboard();
    static std::string keyToLabel(keyboardKey);
    void Draw(Shader &shader);
    void pressKey(keyboardKey key);
    void releaseKey(keyboardKey key);
    std::vector<Key> keys;
private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
    

};
#endif