#include "GameObject.h"
#include "utils/TextureManager.h"
#include <SDL_render.h>

namespace Platformer
{
GameObject::GameObject(const std::string &textureFilePath,
                       SDL_Renderer *&Renderer,
                       int x_Pos,
                       int y_Pos) : xPos(x_Pos), yPos(y_Pos)
{
    mRenderer  = Renderer;
    objTexture = TextureManager::LoadTexture(textureFilePath, mRenderer);
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
    SDL_RenderCopy(mRenderer, objTexture, &srcRect, &dstRect);
}

}  // namespace Platformer
