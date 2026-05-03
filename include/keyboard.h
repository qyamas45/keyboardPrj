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
#include "inputManager.h"
//This is the class that will represent the entire keyboard. 
//It will contain a vector of Key objects, and will be responsible for drawing the keyboard and handling input.
enum class keyboardKey{
    ESCAPE, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
    GRAVE, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO, MINUS, PLUS, BACKSPACE, 
    TAB, Q, W, E, R, T, Y, U, I, O, P, BRACKL, BRACKR, PIPE,
    CAPSLOCK, A, S, D, F, G, H, J, K, L, SEMICOLON, APOSTROPHE, ENTER,
    LSHIFT, Z, X, C, V, B, N, M, COMMA, PERIOD, SLASH, RSHIFT,
    LCTRL, LEFTALT, SPACE, RIGHTALT, RCTRL,
    KEY_COUNT
        
};

class keyboard{ 
public:
    inputManager manager;
    keyboard();
    ~keyboard();
    static std::string keyToLabel(keyboardKey);
    static int keyToGLFWKey(keyboardKey);
    void Draw(Shader&, glm::mat4, glm::mat4);
    void pressKey(keyboardKey);
    void releaseKey(keyboardKey);
    std::vector<Key> keys;
private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
    

};
#endif