
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

    void init();

    void draw(SDL_FRect rect);

    std::filesystem::path mPath;
    float mWidth, mHeight;
    GLuint textureID;
    bool mAnimation;
    int mFrames;
    int mSpeed;
};

}  // namespace Platformer

#endif  // INCLUDE_PLATFORMER_COMPONENT_H_
