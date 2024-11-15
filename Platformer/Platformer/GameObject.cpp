#include "GameObject.h"

#include "Platformer.h"
#include "utils/TextureManager.h"
#include <SDL_render.h>

namespace Platformer
{
GameObject::GameObject(const std::string &textureFilePath,
                       int x_Pos,
                       int y_Pos) : xPos(x_Pos), yPos(y_Pos)
{
    objTexture = TextureManager::LoadTexture(textureFilePath);
}

void GameObject::update()
{
    srcRect.h = 32;
    srcRect.w = 32;
    srcRect.x = 0;
    srcRect.y = 0;

    dstRect.x = xPos++;
    dstRect.y = yPos++;
    dstRect.w = srcRect.w * 2;
    dstRect.h = srcRect.h * 2;
}

void GameObject::render()
{
    SDL_RenderCopy(Game::mRenderer, objTexture, &srcRect, &dstRect);
}

}  // namespace Platformer
