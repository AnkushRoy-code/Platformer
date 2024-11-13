#ifndef INCLUDE_PLATFORMER_GAMEOBJECT_H_
#define INCLUDE_PLATFORMER_GAMEOBJECT_H_

#include <SDL_rect.h>
#include <SDL_render.h>
#include <string>

namespace Platformer
{

class GameObject
{
public:
    GameObject(const std::string &textureFilePath,
               SDL_Renderer *&Renderer,
               int x_Pos,
               int y_Pos);
    ~GameObject() = default;

    void update();
    void render();

private:
    int xPos {}, yPos {};

    SDL_Texture *objTexture {};
    SDL_Rect srcRect {}, dstRect {};
    SDL_Renderer *mRenderer {};
};

}  // namespace Platformer

#endif  // INCLUDE_PLATFORMER_GAMEOBJECT_H_
