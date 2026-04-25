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

void Letter::Draw(char c)
{
    RenderCharOnSurface(c, glm::mat4(1.0f), glm::mat4(1.0f), glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
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

void Letter::RenderCharOnSurface(char c, glm::mat4 model, glm::mat4 view, glm::mat4 projection, glm::vec3 color, float angleDeg)
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

    // Rotate the four quad corners around the key-top center (0, -0.25) in the XZ plane
    float rad  = glm::radians(angleDeg);
    float cosA = cosf(rad);
    float sinA = sinf(rad);
    float cx = 0.0f, cz = -0.25f;
    auto rotXZ = [&](float x, float z, float &rx, float &rz) {
        float dx = x - cx, dz = z - cz;
        rx = cx + dx * cosA - dz * sinA;
        rz = cz + dx * sinA + dz * cosA;
    };

    float x0, z0, x1, z1, x2, z2, x3, z3;
    rotXZ(xpos,     zpos,     x0, z0);   // top-left
    rotXZ(xpos,     zpos - h, x1, z1);   // bottom-left
    rotXZ(xpos + w, zpos - h, x2, z2);   // bottom-right
    rotXZ(xpos + w, zpos,     x3, z3);   // top-right

    // Quad lying flat in the XZ plane (y constant), rotated around key-top center
    float vertices[6][5] = {
        {x0, ypos, z0, 0.0f, 0.0f},
        {x1, ypos, z1, 0.0f, 1.0f},
        {x2, ypos, z2, 1.0f, 1.0f},

        {x0, ypos, z0, 0.0f, 0.0f},
        {x2, ypos, z2, 1.0f, 1.0f},
        {x3, ypos, z3, 1.0f, 0.0f}
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
