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
    for(Key& key : keys)
    {
 
        key.Draw(shader, view, projection);
    }
}
void keyboard::pressKey(keyboardKey key)
{

}
void keyboard::releaseKey(keyboardKey key)
{

}

void keyboard::setupMesh()
{
    const float GAP = 0.05f; // Gap between keys
    const float ROW_D = 0.75f; // Height of each row
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
        else if (i < 52) // Fourth row (Left Shift to Right Shift)
        {
            z = 3 * ROW_D;
            for (size_t j{41}; j < i; ++j)
            {
                x += keys[j].getWidth() + GAP;
            }
        }
        else // Fifth row (Left Ctrl to Right Ctrl)
        {
            z = 4 * ROW_D;
            for (size_t j{52}; j < i; ++j)
            {
                x += keys[j].getWidth() + GAP;
            }
        }
        //std::cout << "Key: " << keys[i].label << ", x: " << x << ", y: " << y << std::endl; // Debug output
        keys[i].position = glm::vec3(x + keys[i].getWidth() / 2.0f, 0.0f, z);
    }
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
        case keyboardKey::ENTER: return "Enter";
        case keyboardKey::SPACE: return " ";
        case keyboardKey::BACKSPACE: return "Backspace";
        case keyboardKey::RSHIFT: return "RShift";
        case keyboardKey::LSHIFT: return "LShift";
        case keyboardKey::LCTRL: return  "Ctrl";
        case keyboardKey::RCTRL: return  "Ctrl";
        case keyboardKey::LEFTALT: return "Alt";
        case keyboardKey::RIGHTALT: return "Alt";
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
        case keyboardKey::ESCAPE: return "Esc";
        case keyboardKey::TAB: return "Tab";
        case keyboardKey::CAPSLOCK: return "Caps Lock";
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