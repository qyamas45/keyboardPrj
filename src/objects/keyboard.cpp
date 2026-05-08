#include "keyboard.h"

keyboard::keyboard()
{
     
    // Initialize keys vector with the appropriate number of keys based on the enum
    keys.reserve(static_cast<size_t>(keyboardKey::KEY_COUNT));
    // Populate the keys vector with Key objects, 
    // using the keyToLabel function to get the label for each key
    for(int i{}; i < static_cast<int>(keyboardKey::KEY_COUNT); ++i)
    {
        keyboardKey keyEnum = static_cast<keyboardKey>(i);
        keys.emplace_back(keyToLabel(keyEnum));
        keys.back().GLFWKey = keyToGLFWKey(keyEnum);
        manager.keys.push_back(&keys.back());
        manager.keyStates.push_back(false);
    }
    setupMesh();

}
keyboard::~keyboard()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void keyboard::Draw(Shader &shader, glm::mat4 view, glm::mat4 projection)
{
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    
    glm::mat4 parentModel = glm::mat4(1.0f);
    parentModel = glm::translate(parentModel, scale);
    base.Draw(shader, parentModel);
    for(Key& key : keys)
    {
        key.Draw(shader, view, projection, parentModel);
    }
    //glfwSetWindowUserPointer(glfwGetCurrentContext(), &manager); // Clear the user pointer after drawing
}
void keyboard::pressKey(keyboardKey key)
{
        
    int idx = static_cast<int>(key);
    if (idx >= 0 && idx < (int)keys.size())
    {
        keys[idx].press(GLFW_PRESS, keys[idx].GLFWKey);
    }
}
void keyboard::releaseKey(keyboardKey key)
{
    int idx = static_cast<int>(key);
    if (idx >= 0 && idx < (int)keys.size())
        keys[idx].release();
}

void keyboard::setupMesh()
{
    const float GAP = 0.05f; // Gap between keys
    const float ROW_D = 0.75f; // Height of each row
    // Compute keyboard footprint
    const float PADDING = 0.9f;
    const float BASE_THICK = 0.2f;
    const float KEY_DEPTH = ROW_D;
    //Define rows as indexs ranges into keys[] (matching in order)
    //for each row:
    //float x = rowStartX; // Starting x position for the row
    //float z = -row * ROW_D;
    //for each key index in row:
    //  keys[i].position = glm::vec3(x+keys[i].getWidth()/2.0f, 0.0f, z);
    //  x += keys[i].getWidth() + GAP; // Move x for the next key, accounting 
    //  for the width of the current key and the gap

    for (size_t i{}; i < keys.size(); ++i)
    {
        float x = 0.0f; // Calculate x based on the key's position in the row
        float z = 0.0f; // Calculate z based on the row number
        if (i < 13) // First row (ESC to F12)
        {
            z = 0.0f;
            for (size_t j{}; j < i; ++j)
            {   
                //std::cout << "Key: " << keys[j].label << ", width: " << keys[j].getWidth() << std::endl; // Debug output
                //Create a an extra grap between F1-F12 and the rest of the keys to visually separate them
                if (j == 0) // After F12
                    x += 0.6f; // Extra gap after F12
                
                else if(j == 4) // After F1-F4
                    x += 0.6f; // Extra gap after F1-F4
                
                else if (j == 8) // After F5-F8
                    x += 0.6f; // Extra gap after F5-F8
                
                else if (j == 12) // After F9-F12
                    x += 0.6f; // Extra gap after F9-F12
                x += keys[j].getWidth() + GAP;
              
            }
        }
        else if (i < 27) // Second row (Tab to Backspace)
        {
            z = ROW_D;
            for (size_t j{13}; j < i; ++j)
            {
                x += keys[j].getWidth() + GAP;
            }
        }
        else if (i < 41) // Third row (Caps Lock to Enter)
        {
            z = 2 * ROW_D;
            for (size_t j{27}; j < i; ++j)
            {
                x += keys[j].getWidth() + GAP;
            }
        }
        else if (i < 54) // Fourth row (Left Shift to Right Shift)
        {
            z = 3 * ROW_D;
            for (size_t j{41}; j < i; ++j)
            {
                x += keys[j].getWidth() + GAP;
            }
        }
        else if (i < 66) // Fifth row (Left Ctrl to Right Ctrl)
        {
            z = 4 * ROW_D;
            for (size_t j{54}; j < i; ++j)
            {
                x += keys[j].getWidth() + GAP;
            }
        }
        else // Fifth row (Left Ctrl to Right Ctrl)
        {
            z = 5 * ROW_D;
            for (size_t j{66}; j < i; ++j)
            {
                x += keys[j].getWidth() + GAP;
            }
        }
        //std::cout << "Key: " << keys[i].label << ", x: " << x << ", y: " << y << std::endl; // Debug output
        keys[i].position = glm::vec3(x + keys[i].getWidth() / 2.0f, 0.0f, z);
    }
    //create the flat base of  the keyboard
    float maxX = 0.0f;
    for (const auto& k : keys)
        maxX = std::max(maxX, k.position.x + k.getWidth() / 2.0f);

    float minZ = -KEY_DEPTH / 2.0f;
    float maxZ =  5.0f * ROW_D + KEY_DEPTH / 2.0f;

    base.position = glm::vec3(maxX / 2.0f, -BASE_THICK / 0.78f, (minZ + maxZ) / 2.0f);
    base.scale    = glm::vec3(maxX + PADDING, BASE_THICK + 0.2, (maxZ - minZ) + PADDING);
    
}

int keyboard::keyToGLFWKey(keyboardKey key)
{
    switch (key)
    {
        case keyboardKey::A: return GLFW_KEY_A;
        case keyboardKey::B: return GLFW_KEY_B;
        case keyboardKey::C: return GLFW_KEY_C;
        case keyboardKey::D: return GLFW_KEY_D;
        case keyboardKey::E: return GLFW_KEY_E;
        case keyboardKey::F: return GLFW_KEY_F;
        case keyboardKey::G: return GLFW_KEY_G;
        case keyboardKey::H: return GLFW_KEY_H;
        case keyboardKey::I: return GLFW_KEY_I;
        case keyboardKey::J: return GLFW_KEY_J;
        case keyboardKey::K: return GLFW_KEY_K;
        case keyboardKey::L: return GLFW_KEY_L;
        case keyboardKey::M: return GLFW_KEY_M;
        case keyboardKey::N: return GLFW_KEY_N;
        case keyboardKey::O: return GLFW_KEY_O;
        case keyboardKey::P: return GLFW_KEY_P;
        case keyboardKey::Q: return GLFW_KEY_Q;
        case keyboardKey::R: return GLFW_KEY_R;
        case keyboardKey::S: return GLFW_KEY_S;
        case keyboardKey::T: return GLFW_KEY_T;
        case keyboardKey::U: return GLFW_KEY_U;
        case keyboardKey::V: return GLFW_KEY_V;
        case keyboardKey::W: return GLFW_KEY_W;
        case keyboardKey::X: return GLFW_KEY_X;
        case keyboardKey::Y: return GLFW_KEY_Y;
        case keyboardKey::Z: return GLFW_KEY_Z;

        case keyboardKey::ESCAPE:    return GLFW_KEY_ESCAPE;
        case keyboardKey::F1:        return GLFW_KEY_F1;
        case keyboardKey::F2:        return GLFW_KEY_F2;
        case keyboardKey::F3:        return GLFW_KEY_F3;
        case keyboardKey::F4:        return GLFW_KEY_F4;
        case keyboardKey::F5:        return GLFW_KEY_F5;
        case keyboardKey::F6:        return GLFW_KEY_F6;
        case keyboardKey::F7:        return GLFW_KEY_F7;
        case keyboardKey::F8:        return GLFW_KEY_F8;
        case keyboardKey::F9:        return GLFW_KEY_F9;
        case keyboardKey::F10:       return GLFW_KEY_F10;
        case keyboardKey::F11:       return GLFW_KEY_F11;
        case keyboardKey::F12:       return GLFW_KEY_F12;
        case keyboardKey::GRAVE:     return GLFW_KEY_GRAVE_ACCENT;
        case keyboardKey::ONE:       return GLFW_KEY_1;
        case keyboardKey::TWO:       return GLFW_KEY_2;
        case keyboardKey::THREE:     return GLFW_KEY_3;
        case keyboardKey::FOUR:      return GLFW_KEY_4;
        case keyboardKey::FIVE:      return GLFW_KEY_5;
        case keyboardKey::SIX:       return GLFW_KEY_6;
        case keyboardKey::SEVEN:     return GLFW_KEY_7;
        case keyboardKey::EIGHT:     return GLFW_KEY_8;
        case keyboardKey::NINE:      return GLFW_KEY_9;
        case keyboardKey::ZERO:      return GLFW_KEY_0;
        case keyboardKey::MINUS:     return GLFW_KEY_MINUS;
        case keyboardKey::PLUS:      return GLFW_KEY_EQUAL;
        case keyboardKey::BACKSPACE: return GLFW_KEY_BACKSPACE;
        case keyboardKey::TAB:       return GLFW_KEY_TAB;
        case keyboardKey::BRACKL:    return GLFW_KEY_LEFT_BRACKET;
        case keyboardKey::BRACKR:    return GLFW_KEY_RIGHT_BRACKET;
        case keyboardKey::PIPE:      return GLFW_KEY_BACKSLASH;
        case keyboardKey::CAPSLOCK:  return GLFW_KEY_CAPS_LOCK;
        case keyboardKey::SEMICOLON: return GLFW_KEY_SEMICOLON;
        case keyboardKey::APOSTROPHE:return GLFW_KEY_APOSTROPHE;
        case keyboardKey::ENTER:     return GLFW_KEY_ENTER;
        case keyboardKey::LSHIFT:    return GLFW_KEY_LEFT_SHIFT;
        case keyboardKey::RSHIFT:    return GLFW_KEY_RIGHT_SHIFT;
        case keyboardKey::COMMA:     return GLFW_KEY_COMMA;
        case keyboardKey::PERIOD:    return GLFW_KEY_PERIOD;
        case keyboardKey::SLASH:     return GLFW_KEY_SLASH;
        case keyboardKey::LCTRL:     return GLFW_KEY_LEFT_CONTROL;
        case keyboardKey::RCTRL:     return GLFW_KEY_RIGHT_CONTROL;
        case keyboardKey::LEFTALT:   return GLFW_KEY_LEFT_ALT;
        case keyboardKey::RIGHTALT:  return GLFW_KEY_RIGHT_ALT;
        case keyboardKey::SPACE:     return GLFW_KEY_SPACE;
        case keyboardKey::KEY_COUNT: return -1;
    }
    return -1;
}
//Util function
std::string keyboard::keyToLabel(keyboardKey key)
{
    switch (key)
    {
        //letters
        case keyboardKey::A: return "A";
        case keyboardKey::B: return "B";
        case keyboardKey::C: return "C";
        case keyboardKey::D: return "D";
        case keyboardKey::E: return "E";
        case keyboardKey::F: return "F";
        case keyboardKey::G: return "G";
        case keyboardKey::H: return "H";
        case keyboardKey::I: return "I";
        case keyboardKey::J: return "J";
        case keyboardKey::K: return "K";
        case keyboardKey::L: return "L";
        case keyboardKey::M: return "M";
        case keyboardKey::N: return "N";
        case keyboardKey::O: return "O";
        case keyboardKey::P: return "P";
        case keyboardKey::Q: return "Q";
        case keyboardKey::R: return "R";
        case keyboardKey::S: return "S";
        case keyboardKey::T: return "T";
        case keyboardKey::U: return "U";
        case keyboardKey::V: return "V";
        case keyboardKey::W: return "W";
        case keyboardKey::X: return "X";
        case keyboardKey::Y: return "Y";
        case keyboardKey::Z: return "Z";

        //special keys
        case keyboardKey::ENTER: return "enter";
        case keyboardKey::SPACE: return " ";
        case keyboardKey::BACKSPACE: return "backspace";
        case keyboardKey::RSHIFT: return "rshift";
        case keyboardKey::LSHIFT: return "lshift";
        case keyboardKey::LCTRL: return  "ctrl";
        case keyboardKey::RCTRL: return  "ctrl";
        case keyboardKey::LEFTALT: return "alt";
        case keyboardKey::RIGHTALT: return "alt";
        case keyboardKey::F1: return "F1";
        case keyboardKey::F2: return "F2";
        case keyboardKey::F3: return "F3";
        case keyboardKey::F4: return "F4";
        case keyboardKey::F5: return "F5";
        case keyboardKey::F6: return "F6";
        case keyboardKey::F7: return "F7";
        case keyboardKey::F8: return "F8";
        case keyboardKey::F9: return "F9";
        case keyboardKey::F10: return "F10";
        case keyboardKey::F11: return "F11";
        case keyboardKey::F12: return "F12";
        case keyboardKey::ESCAPE: return "esc";
        case keyboardKey::TAB: return "tab";
        case keyboardKey::CAPSLOCK: return "caps lock";
        case keyboardKey::GRAVE: return "`";
        case keyboardKey::MINUS: return "-";
        case keyboardKey::PLUS: return "+";
        case keyboardKey::BRACKL: return "[";
        case keyboardKey::BRACKR: return "]";
        case keyboardKey::PIPE: return "\\";
        case keyboardKey::SEMICOLON: return ";";
        case keyboardKey::APOSTROPHE: return "'";
        case keyboardKey::COMMA: return ",";
        case keyboardKey::PERIOD: return ".";
        case keyboardKey::SLASH: return "/";
        //numbers
        case keyboardKey::ONE: return "1";
        case keyboardKey::TWO: return "2";
        case keyboardKey::THREE: return "3";
        case keyboardKey::FOUR: return "4";
        case keyboardKey::FIVE: return "5";
        case keyboardKey::SIX: return "6";
        case keyboardKey::SEVEN: return "7";
        case keyboardKey::EIGHT: return "8";
        case keyboardKey::NINE: return "9";
        case keyboardKey::ZERO: return "0";

        
    }
    // Handle other keys as needed
    // For example:
    
    // Default label for unhandled keys
    return "";
}