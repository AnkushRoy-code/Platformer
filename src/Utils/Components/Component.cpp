#include "Utils/Components/Component.h"
#include "Utils/TextureManager.h"

namespace Platformer
{

SpriteComponent::SpriteComponent(const std::filesystem::path &Path, int Width, int Height) :
    width(Width), height(Height)
{
    textureID = TextureManager::LoadTexture(Path);
}

}  // namespace Platformer
