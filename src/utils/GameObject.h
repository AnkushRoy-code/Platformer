/// Needs work.
#ifndef INCLUDE_PLATFORMER_GAMEOBJECT_H_
#define INCLUDE_PLATFORMER_GAMEOBJECT_H_

#include <SDL_rect.h>
#include <SDL_render.h>
#include <filesystem>
#include <string>

namespace Platformer
{

class GameObject
{
public:
    GameObject(const std::filesystem::path &textureFilePath,
               int x_Pos,
               int y_Pos);
    ~GameObject() = default;

    void update();
    void render();

private:
    int xPos {}, yPos {};

    SDL_Texture *objTexture {};
    SDL_Rect srcRect {}, dstRect {};
};

}  // namespace Platformer

#endif  // INCLUDE_PLATFORMER_GAMEOBJECT_H_
