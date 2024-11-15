#ifndef INCLUDE_UTILS_TEXTUREMANAGER_H_
#define INCLUDE_UTILS_TEXTUREMANAGER_H_

#include <string>
#include <SDL.h>

namespace Platformer
{
class TextureManager
{
public:
    /// @return SDL_Texture
    /// @param std::string filePath
    /// @param SDL_Renderer renderer
    static SDL_Texture *LoadTexture(const std::string &filePath);

    static void Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst);
};
}  // namespace Platformer

#endif  // INCLUDE_UTILS_TEXTUREMANAGER_H_
