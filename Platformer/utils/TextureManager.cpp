#include "TextureManager.h"
#include "Platformer/Platformer.h"
#include <SDL_image.h>

namespace Platformer
{
SDL_Texture *TextureManager::LoadTexture(const std::string &filePath)
{
    SDL_Surface *tmpSurface = IMG_Load(filePath.c_str());
    SDL_Texture *texture =
        SDL_CreateTextureFromSurface(Platformer::Game::mRenderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);

    return texture;
}

void TextureManager::Draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dst)
{
    SDL_RenderCopy(Game::mRenderer, tex, &src, &dst);
}

}  // namespace Platformer
