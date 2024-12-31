#include "Utils/TextureManager.h"

#include <SDL_rect.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace Platformer
{

GLuint TextureManager::LoadTexture(const std::filesystem::path &filePath)
{
    int width, height, channels;
    stbi_set_flip_vertically_on_load(true);

    if (!std::filesystem::exists(filePath))
    {
        std::cerr << "ERROR: Given file doesn't exist: " << filePath << "\n";
    }

    unsigned char *data =
        stbi_load(filePath.string().c_str(), &width, &height, &channels, 0);
    if (!data)
    {
        std::cerr << "Failed to load texture: " << filePath << " - "
                  << stbi_failure_reason() << std::endl;
        return 0;
    }

    // Determine image format
    GLenum format = (channels == 4) ? GL_RGBA : GL_RGB;

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLuint texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Upload the texture data to the GPU
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, data);

    // Free image data and unbind the texture
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

void TextureManager::Draw(GLuint tex, SDL_FRect rect)
{
    // Calculate normalized quad positions
    glBindTexture(GL_TEXTURE_2D, tex);

    // Draw the quad
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(rect.x, rect.y);

    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(rect.x + rect.w, rect.y);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(rect.x + rect.w, rect.y + rect.h);

    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(rect.x, rect.y + rect.h);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);  // Unbind the texture
}

void TextureManager::DrawAnimated(GLuint tex,
                                  SDL_FRect rect,
                                  int frame,
                                  int framesPerRow)
{
    // Fixed height per frame (normalized to 0-1 range)
    float frameWidth = 1.0f / framesPerRow;
    float u          = frameWidth * frame;

    glBindTexture(GL_TEXTURE_2D, tex);

    glBegin(GL_QUADS);
    glTexCoord2f(u, 0);
    glVertex2f(rect.x, rect.y);

    glTexCoord2f(u + frameWidth, 0);
    glVertex2f(rect.x + rect.w, rect.y);

    glTexCoord2f(u + frameWidth, 1.0f);
    glVertex2f(rect.x + rect.w, rect.y + rect.h);

    glTexCoord2f(u, 1.0f);
    glVertex2f(rect.x, rect.y + rect.h);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
}

}  // namespace Platformer
