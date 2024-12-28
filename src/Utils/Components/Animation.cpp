#include "Animation.h"
#include <iostream>

namespace Platformer
{

// You know why I do not have error checking only in some places? One reason is
// I am lazy.

// The reason this has error checking is because I was fucked making this
// because of no error checking

void Animations::addAnimation(const std::filesystem::path &Path,
                              int Width,
                              int Height,
                              int Index)
{
    if (Index >= mAnimations.size())
    {
        mAnimations.resize(Index + 1);
    }
    mAnimations[Index] = Animation(Path, Width, Height);
}

void Animations::addAnimation(const std::filesystem::path &Path,
                              int Width,
                              int Height,
                              int Frames,
                              int Speed,
                              int Index)
{
    if (Index >= mAnimations.size())
    {
        mAnimations.resize(Index + 1);
    }
    mAnimations[Index] = Animation(Path, Width, Height, Frames, Speed);
}

void Animations::init()
{
    for (auto &anim: mAnimations)
    {
        anim.init();
    }
}

void Animations::playAnimation(int Index, SDL_FRect Rect)
{
    if (Index < 0 || Index >= mAnimations.size())
    {
        std::cerr << "Invalid animation index: " << Index << std::endl;
        return;
    }
    mAnimations[Index].draw(Rect);
}
}  // namespace Platformer
