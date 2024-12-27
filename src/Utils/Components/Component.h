
/// Needs work.
#ifndef INCLUDE_PLATFORMER_COMPONENT_H_
#define INCLUDE_PLATFORMER_COMPONENT_H_

#include "Utils/TextureManager.h"
#include <SDL_rect.h>
#include <filesystem>

// Add other Components

namespace Platformer
{
/// Position in 2D space

struct PositionComponent
{
    float x, y;
};

class SpriteComponent
{
public:
    SpriteComponent(const std::filesystem::path &Path, int Width, int Height);
    SpriteComponent(const std::filesystem::path &Path,
                    int Width,
                    int Height,
                    int Frames,
                    int Speed);
    void draw(SDL_FRect rect);

    float width {}, height {};
    GLuint textureID {};

private:
    bool mAnimation = false;
    int mFrames {};
    int mSpeed {};
};

class PlayerSprite : public SpriteComponent
{
public:
    PlayerSprite(const std::filesystem::path &Path, int Width, int Height) :
        SpriteComponent(Path, Width, Height)
    {
    }

    PlayerSprite(const std::filesystem::path &Path,
                 int Width,
                 int Height,
                 int Frames,
                 int Speed) :
        SpriteComponent(Path, Width, Height, Frames, Speed)
    {
    }
};

}  // namespace Platformer

#endif  // INCLUDE_PLATFORMER_COMPONENT_H_
