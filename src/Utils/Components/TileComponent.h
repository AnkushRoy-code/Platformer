#ifndef INCLUDE_COMPONENTS_TILECOMPONENT_H_
#define INCLUDE_COMPONENTS_TILECOMPONENT_H_

#include "SDL_rect.h"

namespace Platformer
{

struct PositionComponent
{
    float x, y;
};

struct CollisionTypeComponent
{
    bool isSolid = true;
};

struct tileTypeComponent
{
    enum TileType
    {
        Grass,
        Dirt,
        Water
    };
};

struct LayerComponent
{
    enum LayerType
    {
        Background,
        Midground,
        Foreground
    } layer;
};


struct RenderComponent
{
    SDL_FRect rect;
};

}  // namespace Platformer

#endif  // INCLUDE_COMPONENTS_TILECOMPONENT_H_
