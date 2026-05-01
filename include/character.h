#ifndef CHARACTER_H
#define CHARACTER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <shader.h>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string>
#include "fileSystem.h"
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class Letter
{
public:
    
    Letter();
    ~Letter();

    FT_Face  face;
    FT_Library ft;
    std::map<GLchar, Character> Characters;

    void Draw(std::string*);
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);
    void RenderCharOnSurface(std::string*, glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 color, float angleDeg = 0.0f);
    
private:
    unsigned int VAO, VBO;
    unsigned int VAO3D, VBO3D;
    Shader textShader;
    Shader text3dShader;
    void setupMesh();
};
#endif
