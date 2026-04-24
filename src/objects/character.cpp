#include "character.h"

Letter::Letter() : textShader("shaders/text.vs", "shaders/text.fs"),
                   text3dShader("shaders/text3d.vs", "shaders/text3d.fs")
{
    setupMesh();
}

Letter::~Letter()
{
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO3D);
    glDeleteBuffers(1, &VBO3D);
}

void Letter::Draw(std::string text)
{
    RenderText(text, 0.0f, 0.0f, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
}

void Letter::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);
    textShader.use();
    textShader.setMat4("projection", projection);
    textShader.setVec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];

        float xpos = x + ch.Bearing.x * scale;
        float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

        float w = ch.Size.x * scale;
        float h = ch.Size.y * scale;

        float vertices[6][4] = {
            {xpos,     ypos + h, 0.0f, 0.0f},
            {xpos,     ypos,     0.0f, 1.0f},
            {xpos + w, ypos,     1.0f, 1.0f},

            {xpos,     ypos + h, 0.0f, 0.0f},
            {xpos + w, ypos,     1.0f, 1.0f},
            {xpos + w, ypos + h, 1.0f, 0.0f}
        };

        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (ch.Advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
}

void Letter::RenderCharOnSurface(char c, glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 color)
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    text3dShader.use();
    text3dShader.setMat4("model", model);
    text3dShader.setMat4("view", view);
    text3dShader.setMat4("projection", projection);
    text3dShader.setVec3("textColor", color);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO3D);

    Character ch = Characters[(GLchar)c];

    // Scale from pixel space to key-local world units
    float s = 0.005f;
    float w = ch.Size.x * s;
    float h = ch.Size.y * s;

    // Center the glyph on the key top face (0, 0.31, -0.25) — y slightly above surface
    float xpos = -w / 2.0f;
    float ypos = 0.31f;
    float zpos = -0.25f + h / 2.0f;

    // Quad lying flat in the XZ plane (y constant); z increases toward key front
    float vertices[6][5] = {
        {xpos,     ypos, zpos,     0.0f, 0.0f},
        {xpos,     ypos, zpos - h, 0.0f, 1.0f},
        {xpos + w, ypos, zpos - h, 1.0f, 1.0f},

        {xpos,     ypos, zpos,     0.0f, 0.0f},
        {xpos + w, ypos, zpos - h, 1.0f, 1.0f},
        {xpos + w, ypos, zpos,     1.0f, 0.0f}
    };

    glBindTexture(GL_TEXTURE_2D, ch.TextureID);
    glBindBuffer(GL_ARRAY_BUFFER, VBO3D);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_BLEND);
}

void Letter::setupMesh()
{
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    std::string fontName = fileSystem::getPath("src/resources/fonts/Monocraft.ttf");

    if (fontName.empty())
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }

    if (FT_New_Face(ft, fontName.c_str(), 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++)
    {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x)};
        Characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    // VAO/VBO for 2D screen-space text (6 vertices x vec4: xy + uv)
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // VAO3D/VBO3D for 3D surface text (6 vertices x 5 floats: vec3 pos + vec2 uv)
    glGenVertexArrays(1, &VAO3D);
    glGenBuffers(1, &VBO3D);
    glBindVertexArray(VAO3D);
    glBindBuffer(GL_ARRAY_BUFFER, VBO3D);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 5, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
