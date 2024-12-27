#ifndef INCLUDE_UTILS_TEXTUREMANAGER_H_
#define INCLUDE_UTILS_TEXTUREMANAGER_H_

#include <filesystem>
#include <SDL.h>
#include <GL/glew.h>

namespace Platformer
{
class TextureManager
{
public:
    /// @return GLuint Texture
    /// @param std::filesystem::path filePath
    static GLuint LoadTexture(const std::filesystem::path &filePath);

    static void Draw(GLuint tex, SDL_FRect rect);

    static void
        DrawAnimated(GLuint tex, SDL_FRect rect, int frame, int framesPerRow);
};
}  // namespace Platformer

#endif  // INCLUDE_UTILS_TEXTUREMANAGER_H_
