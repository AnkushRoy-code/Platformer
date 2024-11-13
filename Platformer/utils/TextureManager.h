#ifndef INCLUDE_UTILS_TEXTUREMANAGER_H_
#define INCLUDE_UTILS_TEXTUREMANAGER_H_

#include <string>
#include <SDL.h>

namespace Platformer
{
class TextureManager
{
public:
    static SDL_Texture *LoadTexture(const std::string &filePath,
                                    SDL_Renderer *&Renderer);
};
}  // namespace Platformer

#endif  // INCLUDE_UTILS_TEXTUREMANAGER_H_
