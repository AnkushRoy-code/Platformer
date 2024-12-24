
/// Needs work.
#ifndef INCLUDE_PLATFORMER_COMPONENT_H_
#define INCLUDE_PLATFORMER_COMPONENT_H_

#include "Utils/TextureManager.h"
#include "Utils/Components/TileComponent.h"
#include <filesystem>

// Add other Components

namespace Platformer
{
/// Position in 2D space

struct SpriteComponent
{
    SpriteComponent(const std::filesystem::path &Path, int Width, int Height);
    float width {}, height {};
    GLuint textureID {};
};

}  // namespace Platformer

#endif  // INCLUDE_PLATFORMER_COMPONENT_H_
