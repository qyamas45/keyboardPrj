#include "key.h"
#include "inputManager.h"   

Key::Key(std::string let) : position(0.0f), rotationAxis(0.0f, 1.0f, 0.0f), 
                            rotationAngle(0.0f), scale(1.0f), color(1.0f)
{
    label = let;
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
void Key::release()
{

}
void Key::setKeyType(std::string keyLabel)
{
    
}
float Key::getWidth() const
{
    return 0.6f + 2.0f * adjustedSize; // Base width plus adjustment for special keys
}
void Key::offSetSize(float& size)
{
   //To be honest, I was thinking more of an efficient way of doing this using switch statements
   //and enums, but since we only have a few special keys, this is fine for now. 
   //We can always refactor later if we add more keys with different sizes.
   if(label == "enter")
   {
    size = 0.57f;
   }
   else if (label == "lshift")
   {
    
    size = 0.52f;
    
   }
   else if (label == "rshift")
   {
    size = 0.69f;
   }
   else if (label == " ")
   {
    size = 1.92f;
   }
   else if (label == "backspace")
   {
    size = 0.58f;
   }
   else if (label == "ctrl")
   {
    size = 0.23f;
   }
   else if (label == "alt")
   {
    size = 0.55f;
   }
   else if (label == "tab")
   {
    size = 0.2258f;
   }
   else if (label == "caps lock")
   {
    size = 0.325f;
   }
   else if (label == "\\")
   {
    size = 0.35f;
   }
}

void Key::setupMesh()
{
    
    //call function to adjust the size based on the letter
    //consider Lshift, RShift, Enter, Space, Backspace, Ctrl, Alt
    //         Tab, CapsLock, etc. that are larger than letter keys
    offSetSize(adjustedSize);
    
    float vertices[] = {
    //front
    //z: -0.3f
    -0.3f-adjustedSize, -0.3f, 0.0f,  0.75f, 0.75f, 0.75f,  // 0 bottom-left
     0.3f+adjustedSize, -0.3f, 0.0f,  0.75f, 0.75f, 0.75f,  // 1 bottom-right
     0.2f+adjustedSize,  0.3f, 0.0f,  0.75f, 0.75f, 0.75f,  // 2 top-right
    -0.2f-adjustedSize,  0.3f, 0.0f,  0.75f, 0.75f, 0.75f,  // 3 top-left

    //sideways (left)
    -0.3f-adjustedSize, -0.3f,  0.0f,  0.75f, 0.75f, 0.75f,  // 4 bottom-right                     
    -0.3f-adjustedSize, -0.3f, -0.5f,  0.75f, 0.75f, 0.75f,  // 5 bottom-left
    -0.2f-adjustedSize,  0.3f,  0.0f,  0.75f, 0.75f, 0.75f,  // 6 top-right
    -0.2f-adjustedSize,  0.3f, -0.5f,  0.75f, 0.75f, 0.75f,  // 7 top-left

    //sideways (right)
    0.3f+adjustedSize, -0.3f,  0.0f,  0.75f, 0.75f, 0.75f,  // 8 bottom-right                     
    0.3f+adjustedSize, -0.3f, -0.5f,  0.75f, 0.75f, 0.75f,  // 9 bottom-left
    0.2f+adjustedSize,  0.3f,  0.0f,  0.75f, 0.75f, 0.75f,  // 10 top-right
    0.2f+adjustedSize,  0.3f, -0.5f,  0.75f, 0.75f, 0.75f,   // 11 top-left

    //back
   -0.3f-adjustedSize, -0.3f, -0.5f,  0.75f, 0.75f, 0.75f,  // 12 bottom-left
    0.3f+adjustedSize, -0.3f, -0.5f,  0.75f, 0.75f, 0.75f,  // 13 bottom-right
    0.2f+adjustedSize,  0.3f, -0.5f,  0.75f, 0.75f, 0.75f,  // 14 top-right
   -0.2f-adjustedSize,  0.3f, -0.5f,  0.75f, 0.75f, 0.75f,  // 15 top-left

    //top
   -0.2f-adjustedSize,  0.3f,  0.0f,  0.75f, 0.75f, 0.75f,  // 16 top-left
    0.2f+adjustedSize,  0.3f,  0.0f,  0.75f, 0.75f, 0.75f,  // 17 top-right
    0.2f+adjustedSize,  0.3f, -0.5f,  0.75f, 0.75f, 0.75f,   // 18 bottom-right
   -0.2f-adjustedSize,  0.3f, -0.5f,  0.75f, 0.75f, 0.75f,   // 19 bottom-left

    //bottom
   -0.3f-adjustedSize, -0.3f,  0.0f,  0.75f, 0.75f, 0.75f,  // 20 top-left
    0.3f+adjustedSize, -0.3f,  0.0f,  0.75f, 0.75f, 0.75f,  // 21 top-right
    0.3f+adjustedSize, -0.3f, -0.5f,  0.75f, 0.75f, 0.75f,   // 22 bottom-right
   -0.3f-adjustedSize, -0.3f, -0.5f,  0.75f, 0.75f, 0.75f   // 23 bottom-left
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
void Key::setColor(glm::vec3 newColor)
{
    color = newColor;
    customColor = true;
}

void Key::Draw(Shader &shader, glm::mat4 view, glm::mat4 projection)
{
    shader.use();
    shader.setBool("useKeyColor", isPressed);
    if (isPressed){
        //std::cout << "Key " << label << " is pressed!" << std::endl; // Debug output
        shader.setVec3("keyColor", glm::vec3(1.0f, 1.0f, 1.0f));
    }
    shader.setVec3("keyColor", color);
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);
    shader.setMat4("model", model);
 

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    
    std::string* labelPtr = &label;
    if (labelPtr)
    {
        float scaleFactor = 1.0f;
        if (label.size() == 1)
            scaleFactor = 0.7f;   // A–Z, digits, symbols
        else if (label == "shift" || label == "lshift" || label == "rshift" ||
                 label == "ctrl"  || label == "alt"    || label == "tab"    ||
                 label == "caps lock" || label == "enter" || label == "backspace")
            scaleFactor = 0.8f;   // modifier / function keys

        letter.RenderCharOnSurface(labelPtr, model, view, projection, glm::vec3(0.0f, 0.0f, 0.0f), 180.0f, 0.2f + adjustedSize, scaleFactor);
        labelPtr++;
    }
        
}
void Key::press(int action, int key)
{
   //PROTOTYPE: This function will eventually handle the visual and functional response to a key press, such as changing the key's color or triggering an animation. 
   //           For now, it just prints the key and action to the console for debugging purposes.
   //if (key == GLFW_KEY_A && action == GLFW_PRESS)
   //{
   //    std::cout << "Key A pressed!" << std::endl;
   //}
    float yOffset = 0.05f; // Example offset value for key press animation

    if (action == GLFW_PRESS)
    {
        //debugging output to verify that the correct key and action are being detected
        //if (key)
        //    std:: cout << "Key " << key << " pressed!" << std::endl;
        //when user presses key, the key will go down and change color to indicate it's being pressed. When the key is released, it will return to its original color.
        //This will be implemented by changing the key's color in the shader and adjusting the position
        
        position.y -= yOffset; // Move the key down by the offset value
        isPressed = true; // Set the key as pressed to change its color in the shader
         
    }
    if(action == GLFW_RELEASE)
    {
        //when user releases key, the key will return to its original position and color. This will be implemented by changing the key's color in the shader and adjusting the position back to its original state.

        position.y += yOffset; // Move the key back up by the offset value
        isPressed = false; // Set the key as not pressed to change its color back in the shader
    }
  
}

void Key::keyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    inputManager* manager = static_cast<inputManager*>(glfwGetWindowUserPointer(window));
    if (manager)
    {
        manager->handleKey(key, action);
    }

    
}