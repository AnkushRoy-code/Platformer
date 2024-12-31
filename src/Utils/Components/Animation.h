#ifndef INCLUDE_COMPONENTS_ANIMATION_H_
#define INCLUDE_COMPONENTS_ANIMATION_H_

#include "Utils/Components/Component.h"

#include <vector>
#include <SDL_rect.h>

namespace Platformer
{

class Animation : public SpriteComponent
{
public:
    Animation() : SpriteComponent("", 0, 0, 0, 0) {}

    Animation(const std::filesystem::path &Path, int Width, int Height) :
        SpriteComponent(
            Path, Width, Height, 1, 1)  // Defaults for Frames and Speed
    {
    }

    Animation(const std::filesystem::path &Path,
              int Width,
              int Height,
              int Frames,
              int Speed) : SpriteComponent(Path, Width, Height, Frames, Speed)
    {
    }
    void drawFlipped(SDL_FRect rect);
};

class Animations
{
public:
    void addAnimation(const std::filesystem::path &Path,
                      int Width,
                      int Height,
                      int Index);

    void addAnimation(const std::filesystem::path &Path,
                      int Width,
                      int Height,
                      int Frames,
                      int Speed,
                      int Index);

    void init();

    void playAnimation(int Index, SDL_FRect Rect, bool dirLeft = true);

private:
    std::vector<Animation> mAnimations;
};

}  // namespace Platformer

#endif  // INCLUDE_COMPONENTS_ANIMATION_H_
