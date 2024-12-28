#include "Animation.h"
#include "Utils/Time.h"
#include <iostream>

namespace Platformer
{

// Why don't I make a function in TextureManager instead of drawing it
// manually here? Because I don't think it is good to add another if
// statement to something used by a lot of things in my game. Also I won't need
// it a lot I think.
void Animation::drawFlipped(SDL_FRect Rect)
{
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBegin(GL_QUADS);

    if (mAnimation && mFrames > 1)
    {
        int frame =
            mWidth * static_cast<int>((Time::getTicks() / mSpeed) % mFrames);

        float frameWidth = 1.0f / mFrames;
        float u          = frameWidth * frame;

        glTexCoord2f(u + frameWidth, 0);
        glVertex2f(Rect.x, Rect.y);

        glTexCoord2f(u, 0);
        glVertex2f(Rect.x + Rect.w, Rect.y);

        glTexCoord2f(u, 1.0f);
        glVertex2f(Rect.x + Rect.w, Rect.y + Rect.h);

        glTexCoord2f(u + frameWidth, 1.0f);
        glVertex2f(Rect.x, Rect.y + Rect.h);
    }

    else
    {
        glTexCoord2f(1.0f, 0.0f);
        glVertex2f(Rect.x, Rect.y);

        glTexCoord2f(0.0f, 0.0f);
        glVertex2f(Rect.x + Rect.w, Rect.y);

        glTexCoord2f(0.0f, 1.0f);
        glVertex2f(Rect.x + Rect.w, Rect.y + Rect.h);

        glTexCoord2f(1.0f, 1.0f);
        glVertex2f(Rect.x, Rect.y + Rect.h);
    }

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

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

void Animations::playAnimation(int Index, SDL_FRect Rect, bool dirLeft)
{
    if (dirLeft)
    {
        if (Index < 0 || Index >= mAnimations.size())
        {
            std::cerr << "Invalid animation index: " << Index << std::endl;
            return;
        }
        mAnimations[Index].draw(Rect);
    }

    else
    {
        if (Index < 0 || Index >= mAnimations.size())
        {
            std::cerr << "Invalid animation index: " << Index << std::endl;
            return;
        }
        mAnimations[Index].drawFlipped(Rect);
    }
}

}  // namespace Platformer
