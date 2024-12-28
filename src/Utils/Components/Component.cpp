#include "Utils/Components/Component.h"
#include "Utils/TextureManager.h"
#include "Utils/Time.h"

#include "SDL_rect.h"

namespace Platformer
{

SpriteComponent::SpriteComponent(const std::filesystem::path &Path,
                                 int Width,
                                 int Height) :
    mWidth(Width), mHeight(Height), mAnimation(false), mFrames(0), mSpeed(0)
{
}

SpriteComponent::SpriteComponent(const std::filesystem::path &Path,
                                 int Width,
                                 int Height,
                                 int Frames,
                                 int Speed) :
    mPath(Path), mWidth(Width), mHeight(Height), mAnimation(true),
    mFrames(Frames), mSpeed(Speed)
{
}

void SpriteComponent::init()
{
    textureID = TextureManager::LoadTexture(mPath);
}

void SpriteComponent::draw(SDL_FRect rect)
{
    if (mAnimation && mFrames != 1)
    {
        int frame =
            mWidth * static_cast<int>((Time::getTicks() / mSpeed) % mFrames);

        TextureManager::DrawAnimated(textureID, rect, frame, mFrames);
    }

    else
    {
        TextureManager::Draw(textureID, rect);
    }
}

}  // namespace Platformer
