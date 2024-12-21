#include "Utils/Component.h"
#include "Utils/TextureManager.h"

namespace Platformer
{

Sprite::Sprite(const std::filesystem::path &Path, int Width, int Height) :
    width(Width), height(Height)
{
    textureID = TextureManager::LoadTexture(Path);
    initialise();
}

Sprite::~Sprite()
{
    deinitialise();
}

void Sprite::initialise()
{
}

void Sprite::deinitialise()
{
}

}  // namespace Platformer
