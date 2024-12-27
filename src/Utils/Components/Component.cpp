#include "Utils/Components/Component.h"
#include "Utils/TextureManager.h"
#include "Utils/Time.h"

#include "SDL_rect.h"

namespace Platformer
{

SpriteComponent::SpriteComponent(const std::filesystem::path &Path,
                                 int Width,
                                 int Height) : width(Width), height(Height)
{
    textureID = TextureManager::LoadTexture(Path);
}

SpriteComponent::SpriteComponent(const std::filesystem::path &Path,
                                 int Width,
                                 int Height,
                                 int Frames,
                                 int Speed)
{
    textureID  = TextureManager::LoadTexture(Path);
    mFrames    = Frames;
    mSpeed     = Speed;
    mAnimation = true;
    width      = Width;
    height     = Height;
}

void SpriteComponent::draw(SDL_FRect rect)
{
    if (mAnimation)
    {
        int frame =
            width * static_cast<int>((Time::getTicks() / mSpeed) % mFrames);
        TextureManager::DrawAnimated(textureID, rect, frame, mFrames);
    }

    else
    {
        TextureManager::Draw(textureID, rect);
    }
}

}  // namespace Platformer
