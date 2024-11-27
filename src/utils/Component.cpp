#include "Component.h"
#include "utils/TextureManager.h"

namespace Platformer
{
// Position Component

// Sprite Component
Sprite::Sprite(const std::filesystem::path &Path, int Width, int Height) :
    width(Width), height(Height)
{
    textureID = TextureManager::LoadTexture(Path);
    initialise();
}

void Sprite::deinitialise()
{
    glDeleteVertexArrays(1, &vaoID);
    glDeleteBuffers(1, &vboID);
    glDeleteBuffers(1, &eboID);
}

Sprite::~Sprite() {
    deinitialise();
}

float vertices[] = {
    // Position       // Texture Coords
    0.0f, 1.0f, 0.0f, 1.0f,  // Top-left
    1.0f, 1.0f, 1.0f, 1.0f,  // Top-right
    1.0f, 0.0f, 1.0f, 0.0f,  // Bottom-right
    0.0f, 0.0f, 0.0f, 0.0f   // Bottom-left
};

unsigned int indices[] = {
    0, 1, 2,  // First Triangle
    2, 3, 0   // Second Triangle
};

void Sprite::initialise()
{
    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboID);
    glGenBuffers(1, &eboID);

    glBindVertexArray(vaoID);

    // Bind and fill the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and fill the element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
                 GL_STATIC_DRAW);

    // Define vertex attribute for position
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)nullptr);
    glEnableVertexAttribArray(0);

    // Define vertex attribute for texture coordinates
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Unbind the VAO (optional)
    glBindVertexArray(0);
}

}  // namespace Platformer
