#include "TextureManager.h"
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_surface.h>

namespace Platformer
{
SDL_Texture *TextureManager::LoadTexture(const std::string &filePath,
                                         SDL_Renderer *&Renderer)
{
    SDL_Surface *tmpSurface = IMG_Load(filePath.c_str());
    SDL_Texture *texture = SDL_CreateTextureFromSurface(Renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return texture;
}

}  // namespace Platformer
