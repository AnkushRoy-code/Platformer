#include "TextureManager.h"
#include "Platformer/Platformer.h"
#include <SDL_image.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace Platformer
{

GLuint TextureManager::LoadTexture(const std::filesystem::path &filePath)
{
    // Load image data using stb_image
    int width, height, channels;
    stbi_set_flip_vertically_on_load(
        true);  // Flip the image vertically for OpenGL
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

    // Generate and bind OpenGL texture
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

    // Generate Mipmaps
    glGenerateMipmap(GL_TEXTURE_2D);

    // Free image data and unbind the texture
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

void TextureManager::Draw(GLuint tex, SDL_Rect src, SDL_Rect dst)
{
    // Calculate normalized texture coordinates
    float texLeft   = (float)src.x / (float)dst.w;
    float texRight  = (float)(src.x + src.w) / (float)dst.w;
    float texTop    = (float)src.y / (float)dst.h;
    float texBottom = (float)(src.y + src.h) / (float)dst.h;

    // Calculate normalized quad positions
    float x0 = (float)dst.x / float(30 * 32) * 2.0f - 1.0f;
    float y0 = 1.0f - (float)dst.y / float(18 * 32) * 2.0f;
    float x1 = x0 + (float)dst.w / float(30 * 32) * 2.0f;
    float y1 = y0 - (float)dst.h / float(18 * 32) * 2.0f;

    // Bind the texture
    glBindTexture(GL_TEXTURE_2D, tex);

    // Draw the quad
    glBegin(GL_QUADS);
    glTexCoord2f(texLeft, texTop);
    glVertex2f(x0, y0);

    glTexCoord2f(texRight, texTop);
    glVertex2f(x1, y0);

    glTexCoord2f(texRight, texBottom);
    glVertex2f(x1, y1);

    glTexCoord2f(texLeft, texBottom);
    glVertex2f(x0, y1);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);  // Unbind the texture
}

}  // namespace Platformer
