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

    void Draw(std::string text);
    void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);

private:
    unsigned int VAO, VBO;
    Shader textShader;
    void setupMesh();
};
#endif
